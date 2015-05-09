
$(document).ready(function init() { // on initialization ...
    var now = new Date();
    
    var servicesEngine = new ServicesEngine();
    var interfaceManager = new InterfaceManager("#location", "#paragraphs");
    var userInputManager = new UserInputManager("#verbList");
    servicesEngine.loadRoom("67646381-0CCA-46EC-9028-A5C2920E97A4", 1, 2, 3, 4, now.toMSJSON());
        
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