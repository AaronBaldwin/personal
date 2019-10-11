const COLOR_CLASSES = ['red', 'orange', 'green', 'blue', 'purple'];
const LIGHTS_CLASS = 'dancing-lights';

let lightsInterval = null;
function startLights(loopAmount) {
  let count = 0;
  if(lightsInterval) clearInterval(lightsInterval);
  lightsInterval = setInterval(function() {
    let lights = document.getElementsByClassName(LIGHTS_CLASS)[0].children;
    for(let i = 0; i < lights.length; i++) {
      if(i % loopAmount === count % loopAmount) lights[i].classList.remove('off');
      else lights[i].classList.add('off');
    }
    count = (count + 1) % loopAmount;
  }, 500);
}

function stopLights() {
  if(lightsInterval) clearInterval(lightsInterval);
  lightsInterval = null;
  let lights = document.getElementsByClassName(LIGHTS_CLASS)[0].children;
  for(let i = 0; i < lights.length; i++) lights[i].classList.remove('off');
}

let $lightsElement = null;
function createLights(parentClassName, height = 5, width = 5) {
  if($lightsElement) $lightsElement.remove();
  let $lights = $(`<div class='${LIGHTS_CLASS}'></div>`);
  for(let i = 0; i < height * width; i++) {
    let colorClassIndex = i % COLOR_CLASSES.length;
    let colorClass = COLOR_CLASSES[colorClassIndex];
    let light = $(`<div class='${colorClass}'></div>`);
    $lights.append(light);
  }
  $lightsElement = $lights;
  $(parentClassName).append($lights);
}

function removeLights() {
  if($lightsElement) $lightsElement.remove();
  lightsElement = null;
}
