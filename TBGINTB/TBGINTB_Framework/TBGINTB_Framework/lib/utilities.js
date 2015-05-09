
Date.prototype.toMSJSON = function () {
    var date = '/Date(' + this.getTime() + ')/';
    return date;
};