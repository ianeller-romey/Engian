
var UserInputManager = function () {
};

UserInputManager.prototype.resetUserInput = function() {
    return this.addCharToUserInput("", "");
};

UserInputManager.prototype.addCharToUserInput = function(add, str) {
    return str.substring(0, str.length - 1) + add + '_';
};

UserInputManager.prototype.deleteCharFromUserInput = function (str) {
    return str.substring(0, str.length - 2) + '_';
};