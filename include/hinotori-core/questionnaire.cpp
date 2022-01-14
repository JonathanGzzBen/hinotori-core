#include "questionnaire.h"

Questionnaire::Questionnaire(QObject *parent) : QObject{parent} {}

Questionnaire::Questionnaire(QString title, QString author,
                             QList<QSharedPointer<Question> > questions,
                             QObject *parent)
    : title{title}, author{author}, questions{questions} {}

bool Questionnaire::SaveQuestionnaire(const Questionnaire &questionnaire,
                                      QString filename) {
  QFile saveFile(filename);
  if (!saveFile.open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open save file.");
    return false;
  }

  QJsonObject questionnaireObj;
  questionnaire.Write(questionnaireObj);
  saveFile.write(QJsonDocument(questionnaireObj).toJson());
  return true;
}

bool Questionnaire::LoadQuestionnaire(Questionnaire &questionnaire,
                                      QString filename) {
  QFile loadFile(filename);
  if (!loadFile.open(QIODevice::ReadOnly)) {
    qWarning("Couldn't open save file");
    return false;
  }

  auto saveData{loadFile.readAll()};
  loadFile.close();
  auto jsonDocument{QJsonDocument::fromJson(saveData)};
  if (!jsonDocument.isObject()) {
    return false;
  }
  questionnaire.Read(jsonDocument.object());
  return true;
}

void Questionnaire::Read(const QJsonObject &json) {
  if (json.contains(kTitleJsonKey) && json[kTitleJsonKey].isString()) {
    title = json[kTitleJsonKey].toString();
  }
  if (json.contains(kAuthorJsonKey) && json[kAuthorJsonKey].isString()) {
    author = json[kAuthorJsonKey].toString();
  }
  if (json.contains(kQuestionsKey) && json[kQuestionsKey].isArray()) {
    QJsonArray questionsArray = json[kQuestionsKey].toArray();
    questions.clear();
    questions.reserve(questionsArray.size());
    for (const auto &questionValueRef : questionsArray) {
      Question question;
      question.Read(questionValueRef.toObject());
      questions.append(QSharedPointer<Question>::create(
          question.Message(), question.CorrrectAnswerIndex(),
          question.PossibleAnswers()));
    }
  }
}

void Questionnaire::Write(QJsonObject &json) const {
  json[kTitleJsonKey] = title;
  json[kAuthorJsonKey] = author;
  QJsonArray questionsArray{};
  for (const auto &question : questions) {
    QJsonObject questionObj;
    question->Write(questionObj);
    questionsArray.append(questionObj);
  }
  json[kQuestionsKey] = questionsArray;
}

QString Questionnaire::Title() { return title; }

QString Questionnaire::Author() { return author; }

QList<QSharedPointer<Question> > Questionnaire::Questions() {
  return questions;
}
