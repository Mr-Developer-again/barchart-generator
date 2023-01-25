#ifndef ARAD_TABLEDRAWING_TABLEWIDGET_TABLEWIDGET_H
#define ARAD_TABLEDRAWING_TABLEWIDGET_TABLEWIDGET_H

#include <headers/scoping.h>

#include <QList>
#include <QTextStream>
#include <QTableWidget>

namespace Arad
{

    namespace TableDrawing
    {

        class TableWidget
        {
            
        public:
            explicit TableWidget(Arad::Scoping::ScopingCls *scopingObj, QTableWidget* parent = nullptr);
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
