
$(document).ready(function init() { // on initialization ...
    var now = new Date();
    
    var servicesEngine = new ServicesEngine();
    var userInputManager = new UserInputManager("#verbList");
    var interfaceManager = new InterfaceManager("#location", "#paragraphs", userInputManager);
    servicesEngine.loadGame(sessionStorage.playerId);
        
    var textParagraphClasses = $(".unParagraph");
    $.each(textParagraphClasses, function (i, textParagraph) {
        $(textParagraph).click(function (e) {
            userInputManager.closeAndReopenVerbList(e.pageX, e.pageY);
        });
    });

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