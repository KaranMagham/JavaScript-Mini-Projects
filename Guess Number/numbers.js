let rannum = Math.floor(Math.random() * 100);
let attempts = 0;

function guess() {
    let userguess = parseInt(document.getElementById("userguess").value);
    let mess = document.getElementById("message");
    attempts++;

    if (isNaN(userguess) || userguess < 0 || userguess > 100) {
        mess.textContent="Please enter a number between 0 to 100."
        return;
    }
    if (userguess < rannum) {
        mess.textContent="Try a bigger number..."
    } else if (userguess > rannum) {
        mess.textContent='Try a smaller number...'
    }else{
        mess.textContent=`🎉 Correct! The number was ${rannum}. Attempts: ${attempts}`;
    }
}
