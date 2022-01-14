#include "question.h"

Question::Question(QObject *parent) : QObject{parent} {}

Question::Question(QString message, qsizetype correctAnswerIndex,
                   QStringList possibleAnswers, QObject *parent)
    : message{message},
      correctAnswerIndex{correctAnswerIndex},
      possibleAnswers{possibleAnswers},
      QObject{parent} {}

bool Question::SaveQuestions(QList<QSharedPointer<Question>> &questions,
                             QString filename) {
  QFile saveFile(filename);
  if (!saveFile.open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open save file.");
    return false;
  }

  QJsonArray questionsArray;
  for (const auto &question : questions) {
    QJsonObject questionObj;
    question->write(questionObj);
    questionsArray.append(questionObj);
  }

  saveFile.write(QJsonDocument(questionsArray).toJson());
  return true;
}

void Question::read(const QJsonObject &json) {
  if (json.contains(kMessageJsonKey) && json[kMessageJsonKey].isString()) {
    message = json[kMessageJsonKey].toString();
  }
  if (json.contains(kCorrectAnswerIndexJsonKey) &&
      json[kCorrectAnswerIndexJsonKey].isDouble()) {
    correctAnswerIndex = json[kCorrectAnswerIndexJsonKey].toInt();
  }
  if (json.contains(kPossibleAnswersJsonKey) &&
      json[kPossibleAnswersJsonKey].isArray()) {
    QJsonArray questionsArray = json[kPossibleAnswersJsonKey].toArray();
    possibleAnswers.clear();
    possibleAnswers.reserve(questionsArray.size());
    for (int possibleAnswerIndex{0};
         possibleAnswerIndex < possibleAnswers.size(); ++possibleAnswerIndex) {
      possibleAnswers[possibleAnswerIndex] =
          questionsArray[possibleAnswerIndex].toString();
    }
  }
}

void Question::write(QJsonObject &json) const {
  json[kMessageJsonKey] = message;
  json[kCorrectAnswerIndexJsonKey] = correctAnswerIndex;
  QJsonArray possibleAnswersArray{QJsonArray::fromStringList(possibleAnswers)};
  json[kPossibleAnswersJsonKey] = possibleAnswersArray;
}
