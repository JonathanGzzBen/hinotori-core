#include "question.h"

Question::Question(QObject *parent) : QObject{parent} {}

Question::Question(QString message, qsizetype correctAnswerIndex,
                   QStringList possibleAnswers, QObject *parent)
    : message{message},
      correctAnswerIndex{correctAnswerIndex},
      possibleAnswers{possibleAnswers},
      QObject{parent} {}

void Question::Read(const QJsonObject &json) {
  if (json.contains(kMessageJsonKey) && json[kMessageJsonKey].isString()) {
    message = json[kMessageJsonKey].toString();
  }
  if (json.contains(kCorrectAnswerIndexJsonKey) &&
      json[kCorrectAnswerIndexJsonKey].isDouble()) {
    correctAnswerIndex = json[kCorrectAnswerIndexJsonKey].toInt();
  }
  if (json.contains(kPossibleAnswersJsonKey) &&
      json[kPossibleAnswersJsonKey].isArray()) {
    QJsonArray possibleAnswersArray = json[kPossibleAnswersJsonKey].toArray();
    possibleAnswers.clear();
    possibleAnswers.reserve(possibleAnswersArray.size());
    for (int possibleAnswerIndex{0};
         possibleAnswerIndex < possibleAnswersArray.size(); ++possibleAnswerIndex) {
      possibleAnswers.append(possibleAnswersArray[possibleAnswerIndex].toString());
    }
  }
}

void Question::Write(QJsonObject &json) const {
  json[kMessageJsonKey] = message;
  json[kCorrectAnswerIndexJsonKey] = correctAnswerIndex;
  QJsonArray possibleAnswersArray{};
  for(const auto&possibleAnswer: possibleAnswers) {
    possibleAnswersArray.append(QJsonValue{possibleAnswer});
  }
  json[kPossibleAnswersJsonKey] = possibleAnswersArray;
}

QString Question::Message() { return message; }

qsizetype Question::CorrrectAnswerIndex() { return correctAnswerIndex; }

QStringList Question::PossibleAnswers() { return possibleAnswers; }
