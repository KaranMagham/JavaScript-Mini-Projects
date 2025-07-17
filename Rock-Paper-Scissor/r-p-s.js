
function play(userchoices) {
    let choices = ["Rock", "Paper", "Scissor"]
    let computerchoices = choices[Math.floor(Math.random() * 3)];
    let result = ""

    if (computerchoices === userchoices) {
        result = "It's a draw...";
    } else if((userchoices === "Rock" && computerchoices === "Scissor") || (userchoices === "Scissor" && computerchoices === "Paper") || (userchoices === "Paper" && computerchoices === "Rock"))
    {
        result = `You Win! ${userchoices} beats ${computerchoices}`;
    } else {
        result = `You Lose! ${computerchoices} beats ${userchoices}`;
    }
    document.getElementById("result").textContent=result;
}

