class Quiz {
  constructor({ title, oneQuestionView, }) {
    this.html = `<div class="quiz"><h2>${title || 'Quiz'}</h2></div>`;
    this.inputName = 0;
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

  getInputName() {
    return this.inputName++;
  }

  render(parentSelector) {
    $(parentSelector).html(this.html);
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
}