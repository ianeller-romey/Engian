(function () {
    "use strict";    
    
    window.addEventListener("load", function load(event) { // initialize once the window has loaded
        window.removeEventListener("load", load, false);
        init();
    }, false);

    
    function init() { // on initialization ...
        var userInputManager = new UserInputManager();
        var engine = new Engine();

        var deleteKey = 8;
        var enterKey = 13;
        var userInput = document.getElementById("user-input");
        userInput.innerHTML = userInputManager.resetUserInput();
        function updateUserInput(event) {
            if (event.keyCode == deleteKey) { // delete characters if the delete key is pressed
                userInput.innerHTML = userInputManager.deleteCharFromUserInput(userInput.innerHTML);
            }
            else if (event.keyCode == enterKey) { // parse characters if the enter key is pressed
                var str = userInput.innerHTML.substring(0, userInput.innerHTML.length - 1);
                if (engine.parse(str) === true) {
                    userInput.innerHTML = userInputManager.resetUserInput();
                }
            }
            else { // otherwise, add characters
                userInput.innerHTML = userInputManager.addCharToUserInput(String.fromCharCode(event.keyCode), userInput.innerHTML);
            }
        };
        window.addEventListener("keypress", function (event) { updateUserInput(event); }, true);

        function suppressBackspace(event) { // we don't want the delete key to act like the browser back button
            event = event || window.event;
            var target = event.target || event.srcElement;
            if (event.keyCode == 8 && !/input|textarea/i.test(target.nodeName)) {
                updateUserInput(event);
                return false;
            }
        };
        document.onkeydown = suppressBackspace;
        document.onkeypress = suppressBackspace;
    };
}());