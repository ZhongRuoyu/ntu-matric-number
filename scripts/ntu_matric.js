function validate() {
    function checksum(type, num) {
        var WEIGHT = [0, 0, 0, 0, 0, 0, 0];
        var OFFSET = 0;
        var RESULTS = ["A", "B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "ERROR"];
        var sum = 0;
        var remainder = 11;
        switch (type) {
            case "U":
                WEIGHT = [6, 7, 4, 3, 8, 9, 2];
                OFFSET = 4;
                break;
            case "B":
                WEIGHT = [10, 7, 4, 3, 2, 9, 8];
                OFFSET = 9;
                break;
        }
        for (var i = 1; i <= 7; i++) {
            sum += (num % 10) * WEIGHT[7 - i];
            num = ~~(num / 10);
        }
        sum += OFFSET;
        remainder = sum % 11;
        return RESULTS[remainder];
    }

    var input = document.getElementById("input");
    var result = document.getElementById("result");
    var type;
    var num;
    var checksum;
    while (input.value.substring(0, 1) == " ") {
        input.value = input.value.substring(1);
    }
    if (input.value.length && !input.value.match(/^[BU]/i)) {
        result.innerHTML =
            "Only numbers starting with B or U are supported at the moment.";
        return;
    }
    if (input.value.length > 9) {
        input.value = input.value.substring(0, 9);
    }
    if (input.value.length < 8) {
        result.innerHTML = "Please enter a matric number.";
        return;
    }
    if (input.value.length == 8 && input.value.match(/^[A-Z]\d{7}/i)) {
        type = input.value.substring(0, 1).toUpperCase();
        num = parseInt(input.value.substring(1, 8));
        result.innerHTML = "The checksum letter is " + checksum(type, num) + ".";
        return;
    }
    if (input.value.match(/^[A-Z]\d{7}[ABCDEFGHJKL]/i)) {
        type = input.value.substring(0, 1).toUpperCase();
        num = parseInt(input.value.substring(1, 8));
        check = input.value.substring(8, 9).toUpperCase();
        if (check == checksum(type, num)) {
            result.innerHTML = input.value.toUpperCase() + " is a valid matric number.";
        } else {
            result.innerHTML = input.value.toUpperCase() + " is not a valid matric number. Please check your input.";
        }
        return;
    }
    if (input.value.match(/^[A-Z]\d{7}[A-Z]/i)) {
        result.innerHTML = input.value.toUpperCase() + " is not a valid matric number. Please check your input.";
        return;
    }
    result.innerHTML = "Invalid input.";
    return;
}
