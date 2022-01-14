#ifndef QUESTION_H
#define QUESTION_H

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QStringList>

#include "hinotori-core_global.h"

class HINOTORICORE_EXPORT Question : public QObject {
  Q_OBJECT
 public:
  explicit Question(QObject *parent = nullptr);
  explicit Question(QString message, qsizetype correctAnswerIndex,
                    QStringList possibleAnswers, QObject *parent = nullptr);
  static bool SaveQuestions(QList<QSharedPointer<Question>> &questions,
                            QString filename);

 private:
  QString message;
  qsizetype correctAnswerIndex;
  QStringList possibleAnswers;

  const QString kMessageJsonKey = "message";
  const QString kCorrectAnswerIndexJsonKey = "correctAnswerIndex";
  const QString kPossibleAnswersJsonKey = "possibleAnswers";

  void read(const QJsonObject &json);
  void write(QJsonObject &json) const;

 signals:
};

#endif  // QUESTION_H
