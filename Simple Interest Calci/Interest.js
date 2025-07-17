function showInterest() {
    let principal = document.getElementById("principalVal").value;
    let rate = document.getElementById("rateVal").value;
    let time = document.getElementById("timeVal").value;

    let interest = (principal * rate * time) / 100;
    let result = `Your interest on your amount is ₹${interest}`;

    document.getElementById("result").textContent = result;
}

