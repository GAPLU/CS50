(() => {
    setTimeout(function(){
    let player = document.getElementsByTagName("video")[0];
    let controls;
    
    button05 = document.createElement("button");
    button05.innerHTML = "0.5";
    button05.className = "btn btn-primary";
    button05.title = "Speed it up";
    button05.style.width = "36px";
    button05.style.height = "36px";
    button05.onclick = function() {
        player.playbackRate = 0.5;
    };

    button1 = document.createElement("button");
    button1.innerHTML = "1";
    button1.className = "btn btn-primary";
    button1.title = "Speed it up";
    button1.style.width = "36px";
    button1.style.height = "36px";
    button1.onclick = function() {
        player.playbackRate = 1;
    };


    button15 = document.createElement("button");
    button15.innerHTML = "1.5";
    button15.className = "btn btn-primary";
    button15.title = "Speed it up";
    button15.style.width = "36px";
    button15.style.height = "36px";
    button15.onclick = function() {
        player.playbackRate = 1.5;
    };

    button2 = document.createElement("button");
    button2.innerHTML = "2";
    button2.className = "btn btn-primary";
    button2.title = "Speed it up";
    button2.style.width = "36px";
    button2.style.height = "36px";
    button2.onclick = function() {
        player.playbackRate = 2;
    };


    button25 = document.createElement("button");
    button25.innerHTML = "2.5";
    button25.className = "btn btn-primary";
    button25.title = "Speed it up";
    button25.style.width = "36px";
    button25.style.height = "36px";
    button25.onclick = function() {
        player.playbackRate = 2.5;
    };

    button3 = document.createElement("button");
    button3.innerHTML = "3";
    button3.className = "btn btn-primary";
    button3.title = "Speed it up";
    button3.style.width = "36px";
    button3.style.height = "36px";
    button3.onclick = function() {
        player.playbackRate = 3;
    };


    button35 = document.createElement("button");
    button35.innerHTML = "3.5";
    button35.className = "btn btn-primary";
    button35.title = "Speed it up";
    button35.style.width = "36px";
    button35.style.height = "36px";
    button35.onclick = function() {
        player.playbackRate = 3.5;
    };

    controls = document.getElementsByClassName("ytp-left-controls")[0];


    let buttonContainer = document.createElement("div");
    buttonContainer.classList.add("button-container");

    buttonContainer.appendChild(button05);
    buttonContainer.appendChild(button1);
    buttonContainer.appendChild(button15);
    buttonContainer.appendChild(button2);
    buttonContainer.appendChild(button25);
    buttonContainer.appendChild(button3);
    buttonContainer.appendChild(button35);

    controls.appendChild(buttonContainer);

    let style = document.createElement('style');
    style.innerHTML = `
    .ytp-left-controls {
        position: relative;
        width: 100%;
    } 
    .button-container {
        display: flex;
        justify-content: flex-end;
        padding-right: 10px;
        padding-top: 5px;
        position: absolute;
        right: 0;
    }

    .button-container button {
        width: 48px;
        height: 48px;
        margin-left: 10px;
        background-color: #444444;
        color: #fff;
        font-size: 16px;
        border: none;
        border-radius: 50%;
        cursor: pointer;
        transition: all 0.2s ease-in-out;
    }
    
    .button-container button:hover {
        background-color: #666666;
    }
    `;
    document.head.appendChild(style);


}, 1000);
})();