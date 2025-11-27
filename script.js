let button1 = document.getElementById("head-one");
let button2 = document.getElementById("head-two");
let button3 = document.getElementById("head-three");

if (button1 !== null) {
  button1.addEventListener("click", open1);
  button2.addEventListener("click", open2);
  button3.addEventListener("click", open3);
}

function open1() {
  let answer = document.getElementById("drop-one");
  button1.classList.toggle("openPlus");
  answer.classList.toggle("open1");
}

function open2() {
  let answer = document.getElementById("drop-two");
  button2.classList.toggle("openPlus");
  answer.classList.toggle("open2");
}

function open3() {
  let answer = document.getElementById("drop-three");
  button3.classList.toggle("openPlus");
  answer.classList.toggle("open3");
}

let d1 = document.getElementById("dorsey-1");
let d2 = document.getElementById("dorsey-2");
let d3 = document.getElementById("dorsey-3");

d1.addEventListener("click", () => increaseImage(d1));
d2.addEventListener("click", () => increaseImage(d2));
d3.addEventListener("click", () => increaseImage(d3));

function increaseImage(d) {
  console.log(d);
  d.classList.toggle("large-img");
}
