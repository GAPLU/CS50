# YouTube Speed Control
#### Video Demo: https://youtu.be/tdQi8dNeXL4
#### Description:
This project is a simple script that allows you to control the playback speed of YouTube videos directly from the player controls. It adds a set of buttons to the player interface, each representing a different playback speed, allowing you to easily switch between speeds without having to access the settings menu. It comprises of manifest.json and content.js files. Manifest.json described a structure of extension (name, description, icon, permissions, etc.). Content.js is a script that makes an extension work. I decided to add a speed-buttons row to the ytp-left-controls row so it's easy to access and therefore convenient to use. I chose a minimalistic style for the buttons and moderate size so it doesn't stick out much. The speed of the YouTube video can be changed in a range [0.5 - 3.5] with 0.5 intervals, which is enough for all needs. The icon is a simple speedometer without any functions implemented into it. All code is inside one content.js file, however this file contains some HTML (such as buttons) as well as CSS (styling for buttons). In a project folder also located an images folder. It contains a few .png files and each of them represents the icon for the extension. The only difference between them is a scale, while it should be a few versions of the image with different scales in order to use them in a distinct "environments" such as phone, tablet, laptop, etc. This project is designed to be lightweight and easy to use, it does not require any additional dependencies or libraries to function properly. It is also compatible with most modern web browsers, including Google Chrome, Firefox, and Safari, making it accessible to a wide range of users. The script is also open-source, and anyone is welcome to contribute to the project by submitting pull requests or by reporting bugs and feature requests in the issue tracker. Overall, this project aims to enhance the user experience by providing an easy and convenient way to control the playback speed of YouTube videos, making it a valuable tool for those who often watch videos at a faster or slower pace. Whether you're a student trying to speed through lectures or a language learner trying to slow down speech, this extension can help you achieve your goals with ease. So, if you're looking for a simple and effective way to control the playback speed of YouTube videos, give this script a try and see how it can enhance your video watching experience.
* Features
    * Customizable playback speeds
    * Easy to use
    * Lightweight
    * Works with most modern web browsers
---
* How to use
   * Install the script by adding it to your browser's extension or userscript manager.
   * Navigate to a YouTube video
   * Click on the new button that appears on the player controls
   * Select your desired playback speed
---
* Compatibility
  * This script is compatible with most modern web browsers, including Google Chrome, Firefox, and Safari.