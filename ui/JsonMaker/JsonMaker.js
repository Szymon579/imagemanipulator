function export2json(red, green, blue) {

    var obj = { "red": red, "green": green, "blue": blue };
    console.log(JSON.stringify(obj));

    //return JSON.stringify(obj);
    return obj;
}
