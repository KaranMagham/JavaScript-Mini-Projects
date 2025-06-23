let arr = [
    "Initializing Hacking...",
    "Analyzing files...",
    "Target found...",
    "Accessing data...",
    "Sending data to server...",
    "Cleaning up..."
];

const randomDelay= function () {
    return new Promise(resolve => {
        const delay = Math.floor(Math.random() * 5 + 1);
        setTimeout(resolve,delay*1000)
        console.log(delay)
    })
}

const terminal = async (it)=>{
    await randomDelay();
    document.getElementById('main').innerHTML += `${it} <br><br>`
}

async function general() {
    for(const item of arr) {
      await terminal(item);
    }
}
general();