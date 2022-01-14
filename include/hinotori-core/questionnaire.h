#ifndef QUESTIONNAIRE_H
#define QUESTIONNAIRE_H

#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QSharedPointer>
#include <QString>

#include "hinotori-core_global.h"
#include "question.h"

class HINOTORICORE_EXPORT Questionnaire : public QObject {
  Q_OBJECT
 public:
  explicit Questionnaire(QObject* parent = nullptr);
  explicit Questionnaire(QString title, QString author,
                         QList<QSharedPointer<Question>> questions,
                         QObject* parent = nullptr);

  static bool SaveQuestionnaire(const Questionnaire& questionnaire,
                                QString filename);
  static bool LoadQuestionnaire(Questionnaire& questionnaire, QString filename);

  void Read(const QJsonObject& json);
  void Write(QJsonObject& json) const;

  QString Title();
  QString Author();
  QList<QSharedPointer<Question>> Questions();

 private:
  QString title;
  QString author;
  QList<QSharedPointer<Question>> questions;

  const QString kTitleJsonKey = "title";
  const QString kAuthorJsonKey = "author";
  const QString kQuestionsKey = "questions";

 signals:
};

#endif  // QUESTIONNAIRE_H
