
var Engine = function () {
    this._verbTables = {};
    var a = 65; // 'A'
    var z = 90; // 'Z'
    for (; a < z; a += 1) {
        this._verbTables[String.fromCharCode(a)] = {};
    }

    // TODO: load this from a db
    this._verbTables["W"][0] = {
        verb: "WALK",
        type: "MOVEMENT"
    };
    this._verbTables["W"].length = 1;
};

Engine.prototype.getverbType = function (str) {
    var char = str[0].toUpperCase();
    var verbTable = this._verbTables[char];
    if (verbTable === undefined) {
        return false;
    }
    str = str.toUpperCase();
    var i = 0;
    for (; i < verbTable.length; i += 1) {
        if (str.indexOf(verbTable[i].verb) === 0) {
            return verbTable[i];
        }
    }
};

Engine.prototype.parse = function (str) {
    var verb = this.getverbType(str);
    if (verb === false) {
        return false;
    }

    return true;
};