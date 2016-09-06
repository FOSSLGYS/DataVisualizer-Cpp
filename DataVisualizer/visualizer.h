#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QLineEdit>
#include <QPointF>

#define MAX_ENTRIES 500
#define INVALID_DATA 65535

namespace Ui {
   typedef enum {
       QUEUE,
       STACK,
       MINHEAP,
       BST
   } dataType;
   void genRand(int *list, int count);
   typedef struct {
       QGraphicsRectItem *rect;
       QGraphicsTextItem *text;
   } RectElement;
   typedef struct {
       QGraphicsEllipseItem *ellipse;
       QGraphicsTextItem *text;
       QGraphicsLineItem *plink;
       QPointF *pos;
   } EllipseElement;

   class list {
   private:
       QGraphicsScene *scene;
       QGraphicsView *view;
       int numEntries;
       QPointF lLabelCoords;
       QLineF  lLineCoords;
       QGraphicsTextItem *lLabel;
       QGraphicsLineItem *lLine;
       QString listData[MAX_ENTRIES];
       std::map<int, Ui::RectElement> lMap;
       QRectF sceneCoords, baseCoords;
   public:
       list() { numEntries=0; }
       ~list();
       explicit list(QGraphicsView *view, QGraphicsScene *scene,
                     QRectF coords, QPointF lP, QLineF lL, QString val);
       void insertNode();
       void removeNode();
       void cleanupNode(Ui::RectElement *node);
       void clearList();
       void incrEntries(int count) { numEntries += count; }
       void decrEntries(int count) { numEntries -= count; }
       int getNumEntries() { return numEntries; }
       void setNextData(QString val) { listData[numEntries+1] = val; }
       int getData(int idx) { return (listData[idx].toInt()); }
       QString getDataStr(int idx) { return (listData[idx]); }
       void setData(int idx, QString val) { listData[idx] = val; }
   };
   typedef class list List;

   class binaryTree {
   private:
       Ui::EllipseElement *tMap[MAX_ENTRIES];
       QString treeData[MAX_ENTRIES];
       int treeHeight;
       int numEntries;
       QRectF sceneCoords, baseCoords;
       QGraphicsScene *scene;
       QGraphicsView *view;

   public:
       binaryTree() { numEntries=0; treeHeight=0; }
       ~binaryTree() { numEntries=0; treeHeight=0; clearTree(); }
       explicit binaryTree(QGraphicsView *view, QGraphicsScene *scene, QRectF coords);
       void insertNode();
       void removeNode();
       void cleanupNode(Ui::EllipseElement *node);
       void clearTree();
       void adjustsceneRect(QRectF offset);
       void incrEntries(int count) { numEntries += count; }
       void decrEntries(int count) { numEntries -= count; }
       int getNumEntries() { return numEntries; }
       void setNextData(QString val) { treeData[numEntries+1] = val; }
       int getData(int idx) { return (treeData[idx].toInt()); }
       QString getDataStr(int idx) { return (treeData[idx]); }
       void setData(int idx, QString val) { if (idx < MAX_ENTRIES) { treeData[idx] = val;} }

   };
   typedef class binaryTree binaryTree;

}

#endif // VISUALIZER_H
