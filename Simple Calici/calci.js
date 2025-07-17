function addition() {
    let n1 = parseFloat(document.getElementById("num1").value);
    let n2 = parseFloat(document.getElementById("num2").value);
    let result = `Addition of two numbers is ${n1 + n2}`;
    document.getElementById("result").textContent = result;
}

function subtraction() {
    let n1 = parseFloat(document.getElementById("num1").value);
    let n2 = parseFloat(document.getElementById("num2").value);
    let result = `Subtraction of two numbers is ${n1 - n2}`;
    document.getElementById("result").textContent = result;
}

function multiplication() {
    let n1 = parseFloat(document.getElementById("num1").value);
    let n2 = parseFloat(document.getElementById("num2").value);
    let result = `Multiplication of two numbers is ${n1 * n2}`;
    document.getElementById("result").textContent = result;
}

function division() {
    let n1 = parseFloat(document.getElementById("num1").value);
    let n2 = parseFloat(document.getElementById("num2").value);

    let result;
    if (!n1 || !n2) {
        result = "Please enter valid numbers.";
    } else if (n2 === 0) {
        result = "Cannot divide by zero!";
    } else {
        result = `Division of two numbers is ${n1 / n2}`;
    }

    document.getElementById("result").textContent = result;
}

