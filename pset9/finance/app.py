import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    id = session.get("user_id")
    row = db.execute("SELECT * FROM users WHERE id = ?", id)
    user = row[0]["username"]
    stocks = db.execute("SELECT * FROM stocks WHERE user = ?", user)
    total = 0
    for stock in stocks:
        stock_price = lookup(stock["stock"])
        stock["price"] = stock_price["price"]
        total = total + stock["price"] * stock['shares']
        stock["total"] = round((stock["price"] * stock["shares"]), 2)
    return render_template("index.html", stocks=stocks, cash=round(row[0]["cash"], 2), total=round((total + row[0]["cash"]), 2), usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("You should fill all lines in", 400)

        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("Shares should be a positive integer", 400)

        shares = int(request.form.get("shares"))

        if shares <= 0:
            return apology("You can buy only positive amount of stocks", 400)

        stock = lookup(request.form.get("symbol"))

        if stock is None:
            return apology("This stock doesn't exist", 400)

        id = session.get("user_id")
        row = db.execute("SELECT * FROM users WHERE id = ?", id)
        cash = row[0]["cash"]

        if (stock["price"] * shares) > cash:
            return apology("You don't have enough money", 400)

        new_cash = cash - stock["price"] * shares
        stock_check = db.execute("SELECT * FROM stocks WHERE user = ? AND stock = ?", row[0]["username"], stock["symbol"])
        if len(stock_check) == 1:
            db.execute("UPDATE stocks SET shares = (shares + ?) WHERE user = ? AND stock = ?",
                       shares, row[0]["username"], stock["symbol"])
        else:
            db.execute("INSERT INTO stocks (user, stock, shares) VALUES(?, ?, ?)", row[0]["username"], stock["symbol"], shares)

        db.execute('UPDATE users SET cash = ? WHERE id = ?', new_cash, id)

        db.execute("INSERT INTO purchases (user, stock, shares, type, price) VALUES(?, ?, ?, ?, ?)",
                   row[0]["username"], stock['symbol'], shares, "bought", stock["price"])
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    id = session.get("user_id")
    row = db.execute("SELECT * FROM users WHERE id = ?", id)
    user = row[0]["username"]
    purchases = db.execute("SELECT * FROM purchases WHERE user = ?", user)
    purchases.reverse()
    return render_template("history.html", purchases=purchases, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        quotes = lookup(request.form.get("symbol"))
        if quotes is None:
            return apology("This symbol doesn't exist")

        return render_template("quoted.html", quotes=quotes, usd=usd)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must create username", 400)

        elif not request.form.get("password"):
            return apology("must create a password", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords should be the same", 400)

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) != 0:
            return apology("username already exists", 400)

        password = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), password)
        rows_id = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        session["user_id"] = rows_id[0]["id"]

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    id = session.get("user_id")
    row = db.execute("SELECT * FROM users WHERE id = ?", id)
    user = row[0]["username"]
    cash = row[0]["cash"]
    shares = db.execute("SELECT * FROM stocks WHERE user = ?", user)
    if request.method == "POST":
        count = 0
        for share in shares:
            if request.form.get("symbol") == share['stock']:
                count = count + 1

        if count == 0:
            return apology("you should select stock", 400)

        if int(request.form.get("shares")) < 0:
            return apology("you can't sell negative amount of shares", 400)

        your_stock = db.execute("SELECT * FROM stocks WHERE user = ? AND stock = ?", user, request.form.get('symbol'))
        if int(request.form.get("shares")) > your_stock[0]['shares']:
            return apology("you don't have shares", 400)

        stock_price = lookup(request.form.get("symbol"))
        new_cash = cash + (int(request.form.get("shares")) * stock_price["price"])
        db.execute('UPDATE users SET cash = ? WHERE id = ?', new_cash, id)
        new_shares = your_stock[0]['shares'] - int(request.form.get("shares"))
        if new_shares == 0:
            db.execute('DELETE FROM stocks WHERE id = ? AND stock = ?', user, request.form.get('symbol'))

        else:
            db.execute('UPDATE stocks SET shares = ? WHERE user = ? AND stock = ?', new_shares, user, request.form.get('symbol'))

        db.execute("INSERT INTO purchases (user, stock, shares, type, price) VALUES(?, ?, ?, ?, ?)", user,
                   request.form.get('symbol'), int(request.form.get("shares")), "sold", stock_price["price"])

        return redirect("/")

    else:
        return render_template("sell.html", shares=shares)


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """"changes password"""
    id = session.get("user_id")
    row = db.execute("SELECT * FROM users WHERE id = ?", id)
    password_hash = row[0]['hash']
    if request.method == "POST":
        if not request.form.get("new_password") or not request.form.get("current_password") or not request.form.get("confirmation"):
            return apology("all lines should be filled")

        if check_password_hash(password_hash, request.form.get("current_password")) == False:
            return apology("incorrect current password", 403)

        if request.form.get("new_password") != request.form.get("confirmation"):
            return apology("passwords should be the same", 403)

        if request.form.get("new_password") == request.form.get("current_password"):
            return apology("you can't use current password")

        new_password = generate_password_hash(request.form.get("new_password"))
        db.execute("UPDATE users SET hash = ? WHERE id = ?", new_password, id)

        return redirect("/")

    else:
        return render_template("change_password.html")
