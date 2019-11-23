function shuffleArray(array) {
  for (let i = array.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [array[i], array[j]] = [array[j], array[i]];
  }
}

class RadioGroup {
  constructor({title, choices, radioGroupName }) {
    let optionsHtml = choices.map(this.buildOptionHtml).join('');

    this.radioGroupName = radioGroupName;
    this.html = `<div group=${radioGroupName} class="radio-group">
      <p>${title}</p>
      ${optionsHtml}
    </div>`;
  }

  buildOptionHtml(value) {
    return `<div class="radio-option" value=${value}>
      <div class="radio-icon"></div><p>${value}</p>
    </div>`;
  }

  selectOption = (value) => {
    $(`.radio-group[group="${this.radioGroupName}"] .radio-option`)
      .removeClass('selected');

    $(`.radio-group[group="${this.radioGroupName}"] .radio-option[value="${value}"]`)
      .addClass('selected');
  }

  render(parentSelector, append=false) {
    const parent = $(parentSelector);
    const selectOption = this.selectOption;

    if(append) parent.append(this.html);
    else parent.html(this.html);

    $(`.radio-group[group="${this.radioGroupName}"] .radio-option`)
    .each(function(index, radioOption) {
      const jRadioOption = $(radioOption);
      jRadioOption.click(() => { console.log('click found'); selectOption(jRadioOption.attr('value')) })
    })
  }
}

class Quiz {
  constructor({ title, oneQuestionView, questions }) {
    this.quizClass = oneQuestionView ? `quiz one-q-view` : `quiz`;
    this.correctAnswers = [];
    this.inputName = 0;

    this.questions = questions.map(this.buildQuestion);

    this.html = `<div class="${this.quizClass}">
      <h2>${title || 'Quiz'}</h2>
      <div class="questions"></div>
      <br />
      <a class="submit-answers">Submit</a>
    </div>`;
  }

  buildQuestion = (oneQuestion) => {
    const { question, answer, otherOptions } = oneQuestion;

    const title = question;
    const radioGroupName = this.getInputName();

    // Add this answer to the array of correct answers, for later check
    this.correctAnswers.push(answer);

    // All of the options for this question in one array
    let choices = otherOptions.concat([answer]);
    shuffleArray(choices);

    return new RadioGroup({title, choices, radioGroupName});
  }

  getInputName() {
    return this.inputName++;
  }

  submitAnswers() {
    console.log('answers submitted');
  }

  render(parentSelector) {
    $(parentSelector).html(this.html);
    this.questions.forEach(radioGroup => {
      radioGroup.render(`${parentSelector} .quiz .questions`, true);
    })
    $('.quiz .submit-answers').click(this.submitAnswers);
  }
}

let questions = {
  "title": "Act I Quiz",
  "oneQuestionView": true,
  "questions": [
    {
      "question": "Who is engaged to Mariane?",
      "answer": "Valere",
      "otherOptions": ["Orgon", "Damis", "Cleante"]
    },
    {
      "question": "Which of these characters is partial to Tartuffe?",
      "answer": "Madame Pernelle",
      "otherOptions": ["Cleante", "Dorine", "Damis"]
    },
    {
      "question": "Which character had some sort of flu?",
      "answer": "Elmire",
      "otherOptions": ["Tartuffe", "Orgon", "Madame Pernelle"]
    }
  ]
}

let quiz = new Quiz(questions);
quiz.render('body');
