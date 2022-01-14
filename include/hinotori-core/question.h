#ifndef QUESTION_H
#define QUESTION_H

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
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

  void Read(const QJsonObject &json);
  void Write(QJsonObject &json) const;

  QString Message();
  qsizetype CorrrectAnswerIndex();
  QStringList PossibleAnswers();

 private:
  QString message;
  qsizetype correctAnswerIndex;
  QStringList possibleAnswers;

  const QString kMessageJsonKey = "message";
  const QString kCorrectAnswerIndexJsonKey = "correctAnswerIndex";
  const QString kPossibleAnswersJsonKey = "possibleAnswers";

 signals:
};

#endif  // QUESTION_H
