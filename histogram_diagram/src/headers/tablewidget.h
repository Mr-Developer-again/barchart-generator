#ifndef ARAD_TABLEDRAWING_TABLEWIDGET_TABLEWIDGET_H
#define ARAD_TABLEDRAWING_TABLEWIDGET_TABLEWIDGET_H

#include <headers/scoping.h>

#include <QList>
#include <QTextStream>
#include <QTableWidget>
#include <QDialog>

namespace Arad
{

    namespace TableDrawing
    {

        class TableWidget : public QDialog
        {
            Q_OBJECT
            
        public:
            explicit TableWidget(Arad::Scoping::ScopingCls *scopingObj, QWidget* parent = nullptr);
            virtual ~TableWidget();

            virtual void draw();

        protected:
            void setColumnLabels(QList<QString> const&);
            QList<QString> const& getColumnLabels() const;
            
            void setRowLabels(QList<QString> const&);
            QList<QString> const& getRowLabels() const;
        private:
            QTableWidget *_tableWidget = nullptr;
            Arad::Scoping::ScopingCls *_scopingObj = nullptr;

            QList<QString> _rowLabels;
            QList<QString> _columnLabels;
        };
        
    } // TableDrawing namespace

} // Arad namespace

#endif // ARAD_TABLEDRAWING_TABLEWIDGET_TABLEWIDGET_H
