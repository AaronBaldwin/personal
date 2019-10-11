$(document).ready(function() {

$('.sidebar .book .click-wrapper').click(function() {
  $(this).parent().toggleClass('open');

});

});

class Quiz {
  constructor() {
    this.html = '<div class="quiz"></div>';
    this.inputName = 0;
  }

  getInputName() {
    return this.inputName++;
  }

  render(parentSelector) {
    $(parentSelector).html(this.html)
  }

  addTrueFalse(question) {
    let inputName = this.getInputName();
    let html = `<div class="true-false">
      <p>${question}</p>
      <input type="radio" name=${inputName} value="true"/>True
      <input type="radio" name=${inputName} value="false"/>False
    </div>`;

    $('.quiz').append(html);
  }

  addMultipleChoice(choices, title) {
    let inputName = this.getInputName();
    choices.sort(() => Math.random() - 0.5);
    let choicesHtml = choices.reduce((htmlString, choice, index) => {
      let updatedString = htmlString +
        `<input type="radio" name=${inputName} value=${index}/>${choice}<br />`;
      return updatedString;
    });

    let html = `<div class="multi-choice">
      <p>${title}</p>
      ${choicesHtml}
    </div>`;

    $('.quiz').append(html);
  }
}

let quiz = new Quiz;
quiz.render('.right');