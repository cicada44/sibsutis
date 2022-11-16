const arr_images_src =
    [
      '../icons/film_icons/rev/main.jpg', '../icons/film_icons/rev/s1.jpg',
      '../icons/film_icons/rev/s2.jpeg', '../icons/film_icons/rev/s3.webp',
      '../icons/film_icons/rev/s4.jpg'
    ]

    var cnter = 0;

function rollover(obj) {
  obj.src = arr_images_src[cnter];
  cnter += 1;
}

var slides_cnter = 0;

function showSlides() {
  var imgb = document.getElementById('imgbox');
  imgb.src = arr_images_src[slides_cnter];
  console.log(imgb.src, slides_cnter);
  ++slides_cnter;
  if (slides_cnter == 5) slides_cnter = 0;
  setTimeout(showSlides, 2500);
}

showSlides();
