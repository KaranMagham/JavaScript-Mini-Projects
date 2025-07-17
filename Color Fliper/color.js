 const boxes=[
    document.getElementById("box1"),
    document.getElementById("box2"),
    document.getElementById("box3"),
    document.getElementById("box4")
 ];

 function randomColor() {
    const letter= "0123456789ABCDEF";
    let color= "#";
    for (let i = 0; i < 6; i++) {
        color += letter[Math.floor(Math.random()*16)];
    }
    return color;
 }

 function changeColor() {
    boxes.forEach(box =>{
        box.style.backgroundColor=randomColor();
    });
 }