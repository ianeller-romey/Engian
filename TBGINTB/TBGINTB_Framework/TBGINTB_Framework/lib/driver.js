(function () {
    "use strict";
    
    window.addEventListener("load", function load(event) { // initialize once the window has loaded
        window.removeEventListener("load", load, false);
        init();
    }, false);

    
    function init() { // on initialization ...
        var userInputManager = new UserInputManager();
        var engine = new Engine();
        
        var i = 0;
        var textParagraphs = document.getElementsByClassName("unParagraph");
        var verbListElem = document.getElementById("verbList");
        var interfaceElem = document.getElementById("interface");

        var openVerbListElem = function (event) {
            verbListElem.style.left = (event.clientX - interfaceElem.offsetLeft) + "px";
            verbListElem.style.top = (event.clientY - interfaceElem.offsetTop - 20) + "px";
            var div = document.createElement("div");
            div.className = "verb";
            div.innerHTML = "TEST";
            div.addEventListener("click", closeVerbListElem, true);
            verbListElem.appendChild(div);
        };
        var closeVerbListElem = function (event) {
            while (verbListElem.firstChild) {
                verbListElem.removeChild(verbListElem.firstChild);
            }
        };

        for (; i < textParagraphs.length; i += 1) {
            textParagraphs[i].addEventListener("click", closeVerbListElem, true);
            textParagraphs[i].addEventListener("click", openVerbListElem, true);
        }

        /*
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
        */

        
    };
}());