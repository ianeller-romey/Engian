
$(document).ready(function init() { // on initialization ...
    var userInputManager = new UserInputManager();
    var engine = new Engine();
        
    var i = 0;
    var textParagraphs = document.getElementsByClassName("unParagraph");
    var verbListElem = $("#verbList");
    var interfaceElem = document.getElementById("interface");

    var openVerbListElem = function (event) {
        var div = document.createElement("div");
        div.className = "verb";
        div.innerHTML = "TEST";
        div.addEventListener("click", closeVerbListElem, true);
        verbListElem.append(div);
        verbListElem.animate({
            left: event.clientX - interfaceElem.offsetLeft,
            top: event.clientY - interfaceElem.offsetTop - 20,
            width: (4 * 20) + 20,
            padding: "0 10 0 10"
        }, function () {
            verbListElem.animate({
                height: (1 * 20) + 20,
                padding: 10
            })
        });
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

        
});