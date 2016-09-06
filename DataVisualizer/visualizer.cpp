// This file consists of utility APIs
// needed for visualizer datastructures such as
// lists/trees. This provides a common interface
// that can be used across various datastructures.
#include <visualizer.h>

Ui::List::list(QGraphicsView *v, QGraphicsScene *s,
           QRectF coords, QPointF lP, QLineF lL, QString val)
{
    view = v;
    scene = s;
    scene->setSceneRect(coords);
    scene->setFocus();
    sceneCoords = baseCoords = coords;
    numEntries = 0;

    QFont font;
    font.bold();
    lLabel = scene->addText(val, font);
    lLabel->setPos(lP);
    lLine = scene->addLine(lL);
    lLineCoords = lL;
    lLabelCoords = lP;
}

Ui::List::~list()
{
    if (lLabel)
       delete lLabel;
    if (lLine)
       delete lLine;
}

void Ui::List::cleanupNode(Ui::RectElement *elem) {
    QGraphicsTextItem *l = elem->text;
    QGraphicsRectItem *r = elem->rect;
    scene->removeItem(l);
    scene->removeItem(r);
    delete l;
    delete r;
}

void Ui::List::insertNode()
{
    QFont font;
    QGraphicsTextItem *l;
    QGraphicsRectItem *r;
    Ui::RectElement elem;
    QPen pen;

    font.bold();
    pen.setBrush(Qt::red);
    font.setBold(1);
    font.setWeight(10);
    if (numEntries==1) { // Add first node
        view->setScene(scene);
        l = scene->addText(getDataStr(numEntries-1), font);
        l->setPos(lLineCoords.x2()-10, lLineCoords.y2()-30);
        r = scene->addRect(lLineCoords.x2()-20, lLineCoords.y2()-40, 50, 40, pen);
    } else { // Add consequetive nodes and set the top at the right position.
        l = scene->addText(getDataStr(numEntries-1), font);
        lLabelCoords.setX(lLabelCoords.x()+50);
        lLabel->setPos(lLabelCoords);
        lLineCoords.setLine(lLineCoords.x1()+50, lLineCoords.y1(), lLineCoords.x2()+50, lLineCoords.y2());
        lLine->setLine(lLineCoords);
        l->setPos(lLineCoords.x2()-10, lLineCoords.y2()-30);
        r = scene->addRect(lLineCoords.x2()-20, lLineCoords.y2()-40, 50, 40, pen);
    }

    elem.text = l;
    elem.rect = r;
    lMap.insert(std::make_pair(numEntries, elem));
}

void Ui::List::removeNode()
{
    std::map<int, Ui::RectElement>::iterator it;

    // Clean up the last element
    it = lMap.find(numEntries+1);
    if (it != lMap.end()) {
        Ui::RectElement elem = it->second;
        cleanupNode(&elem);
        lMap.erase(it);
    }

    for (int i=1; i<numEntries+1; i++)
    {
        it = lMap.find(i);
        if (it != lMap.end()) {
            Ui::RectElement elem = it->second;
            QGraphicsTextItem *t = elem.text;
            t->setPlainText(getDataStr(i-1));
        }
    }

    // Move the label to point to the right position
    if (numEntries) {
        lLabelCoords.setX(lLabelCoords.x()-50);
        lLabel->setPos(lLabelCoords);
        lLineCoords.setLine(lLineCoords.x1()-50, lLineCoords.y1(), lLineCoords.x2()-50, lLineCoords.y2());
        lLine->setLine(lLineCoords);
    }
}

void Ui::List::clearList()
{
    std::map<int, Ui::RectElement>::iterator it;

    if  (!numEntries)
        return; // Do Nothing

    for (int i=1; i<(numEntries+1); i++) {
         it = lMap.find(i);
         if (it != lMap.end()) {
             Ui::RectElement elem = it->second;
             cleanupNode(&elem);
             lMap.erase(it);
         }
    }
    lLabelCoords.setX(lLabelCoords.x()-50*(numEntries-1));
    lLabel->setPos(lLabelCoords);
    lLineCoords.setLine(lLineCoords.x1()-50*(numEntries-1), lLineCoords.y1(), lLineCoords.x2()-50*(numEntries-1), lLineCoords.y2());
    lLine->setLine(lLineCoords);
    numEntries=0;
}

Ui::binaryTree::binaryTree(QGraphicsView *v, QGraphicsScene *s, QRectF coords)
{
    view = v;
    scene = s;
    scene->setSceneRect(coords);
    scene->setFocus();
    sceneCoords = baseCoords = coords;
    numEntries = 0;

    for (int idx = 0; idx < MAX_ENTRIES; idx++) {
        QString val = QString::number(INVALID_DATA);
        treeData[idx] = val;
    }
}

// API to adjust scene size if the tree grows
// bigger.
void Ui::binaryTree::adjustsceneRect(QRectF offset)
{
    if (offset.height() > sceneCoords.height()) {
        if (offset.y() > 0) {
            offset.setY(sceneCoords.y()-(offset.y()-sceneCoords.y()));
        }
        sceneCoords.setX(offset.y()); sceneCoords.setY(offset.y());
        sceneCoords.setWidth(offset.height()); sceneCoords.setHeight(offset.height());
    } else if (offset.width() > sceneCoords.width()) {
        if (offset.x() > 0) {
            offset.setX(sceneCoords.x()-(offset.x()-sceneCoords.x()));
        }
        sceneCoords.setX(offset.x()); sceneCoords.setY(offset.x());
        sceneCoords.setWidth(offset.width()); sceneCoords.setHeight(offset.width());
    }
    view->setSceneRect(sceneCoords.x(),sceneCoords.y(), sceneCoords.width(), sceneCoords.height());
}

void Ui::binaryTree::insertNode()
{
    Ui::EllipseElement *node;
    QFont font;

    node = new Ui::EllipseElement;
    if (node == NULL) {
        return; //Bail out -- NO MEM
    }

    font.setBold(0);
    if (numEntries==1) {
        // Insert the first node at top left of the scene.
        node->pos = new QPointF;
        node->pos->setX(-120); node->pos->setY(-240);
        QGraphicsEllipseItem *e = scene->addEllipse(node->pos->x(), node->pos->y(), 40, 20);
        scene->setFocusItem(e, Qt::OtherFocusReason);
        node->ellipse = e;
        node->ellipse->setFlag(QGraphicsItem::ItemIsMovable, true);
        node->text = scene->addText(treeData[numEntries-1], font);
        node->text->setPos(node->pos->x()+8, node->pos->y());
        node->plink = NULL;
        tMap[numEntries] = node;
        treeHeight=1;
    } else {

       // Adjust the previous entries for position + contents
       // after the new insert.

       int newHeight = (int)(log2((double)numEntries));
       int leaves = pow(2,newHeight);
       double offset=0;
       int currHeight, prevHeight;
       currHeight=prevHeight=0;
       for (int pos=1; pos<numEntries; pos++) {
            currHeight = (int)log2((double)pos);
            // If the height is not balanced
            // then we have an invalid value at the
            // position.
            if (treeData[pos-1].toInt() == INVALID_DATA) {
                continue;
            }

            Ui::EllipseElement *n = tMap[pos];
            QGraphicsTextItem *t = n->text;
            // If the height increase, we need to position
            // the nodes farther to make room for the next level.
            if (newHeight>treeHeight) {
                Ui::EllipseElement *parent = tMap[pos/2];
                // If we are at (height > 1), the nodes
                // have to be moved according to the parent.
                if (pos/2) {
                    QGraphicsLineItem *l = n->plink;
                    QLineF line = l->line();
                    // If the new height of our treeData is N, we have
                    // 2^N leaves. Out of that, we will have 1/2^currHeight
                    // for the subtree rooted at "currHeight". We
                    // want to know that so we can position ourselves
                    // right to make room for the subtrees/leaves.
                    if ((currHeight != prevHeight) &&
                        (treeData[pos].toInt() != INVALID_DATA) &&
                         (getData(2*(pos-1)) != INVALID_DATA)) {
                        offset = leaves/pow(2,currHeight);
                        prevHeight = currHeight;
                    } else {
                        // Keep the offset the same if the tree is sparse.
                        prevHeight = currHeight;
                        offset = 1;
                    }
                    if (pos%2) {
                        n->pos->setX(parent->pos->x()+(offset*50)); n->pos->setY(n->pos->y()+10);
                        line.setLine(n->pos->x()+25, n->pos->y(), parent->pos->x()+10, parent->pos->y()+20);
                    } else {
                        n->pos->setX(parent->pos->x()-(offset*50)); n->pos->setY(n->pos->y()+10);
                        line.setLine(n->pos->x()+25, n->pos->y(), parent->pos->x()+10, parent->pos->y()+20);
                    }
                    l->setLine(line);
                } else {
                    n->pos->setX(n->pos->x()+newHeight*50);
                }
                // Set the right position for the ellipse and the text as calculated
                QGraphicsEllipseItem *e = n->ellipse;
                e->setRect(n->pos->x(), n->pos->y(), 40, 20);
                t->setPos(n->pos->x()+8, n->pos->y());

                //Adjust the scene size if we are expanding
                qreal new_w = (n->pos->x())*2;
                qreal new_h = ((int)n->pos->y())*2;

                if ((new_w > (int)sceneCoords.width()) || (new_h > (int)sceneCoords.height())) {
                    QRectF coords;
                    coords.setX(n->pos->x()); coords.setY(n->pos->y());
                    coords.setWidth(abs(new_w)); coords.setHeight(abs(new_h));
                    adjustsceneRect(coords);
                }
            }
            t->setPlainText(treeData[pos-1]);
        }
        treeHeight = log2((double)numEntries);
        if (!(numEntries%2)) { // Insert the Left Child to the left of its parent
            Ui::EllipseElement *parent = tMap[numEntries/2];
            if (parent != NULL) {
                node->pos = new QPointF;
                node->pos->setX(parent->pos->x()-50); node->pos->setY(parent->pos->y()+30);
                node->ellipse = scene->addEllipse(node->pos->x(), node->pos->y(), 40, 20);
                node->ellipse->setFlag(QGraphicsItem::ItemIsMovable, true);
                node->text = scene->addText(treeData[numEntries-1], font);
                node->text->setPos(node->pos->x()+8, node->pos->y());
                node->plink= scene->addLine(node->pos->x()+20, node->pos->y(), parent->pos->x()+10, parent->pos->y()+20);
                tMap[numEntries] = node;
             }
        } else { // Insert the Right Child at the right of its parent
            Ui::EllipseElement *parent = tMap[numEntries/2];
            if (parent != NULL) {
                node->pos = new QPointF;
                node->pos->setX(parent->pos->x()+50); node->pos->setY(parent->pos->y()+30);
                node->ellipse = scene->addEllipse(node->pos->x(), node->pos->y(), 40, 20);
                node->ellipse->setFlag(QGraphicsItem::ItemIsMovable, true);
                node->text = scene->addText(treeData[numEntries-1], font);
                node->text->setPos(node->pos->x()+8, node->pos->y());
                node->plink = scene->addLine(node->pos->x()+10, node->pos->y(), parent->pos->x()+20, parent->pos->y()+20);
                tMap[numEntries] = node;
            }
        }
        // Adjust the scene size if we need to
        int new_w = ((int)node->pos->x())*2;
        int new_h = ((int)node->pos->y())*2;

        if ((new_w > (int)sceneCoords.width()) || (new_h > (int)sceneCoords.height())) {
            QRectF coords;
            coords.setX(node->pos->x()); coords.setY(node->pos->y());
            coords.setWidth(abs(new_w)); coords.setHeight(abs(new_h));
            adjustsceneRect(coords);
        }
    }
}

void Ui::binaryTree::cleanupNode(Ui::EllipseElement *node)
{
    scene->removeItem(node->ellipse);
    scene->removeItem(node->text);
    if (node->plink != NULL) {
        scene->removeItem(node->plink);
    }
    delete node->ellipse;
    delete node->text;
    delete node->pos;
    delete node->plink;
    delete node;
}

void Ui::binaryTree::removeNode()
{
    //Cleanup the old node
    cleanupNode(tMap[numEntries+1]);

    QFont font;
    int newHeight = (int)(log2((double)numEntries));
    int leaves = pow(2,newHeight);
    double offset=0;
    int currHeight, prevHeight;
    currHeight=prevHeight=0;
    for (int pos=1; pos<(numEntries+1); pos++) {
         Ui::EllipseElement *n = tMap[pos];
         QGraphicsTextItem *t = n->text;
         currHeight = (int)log2((double)pos);
         // If the height decreases, we can shrink the tree
         // to make room for further inserts
         if (newHeight<treeHeight) {
             Ui::EllipseElement *parent = tMap[pos/2];
             // If we are at (height > 1), the node
             // have to be moved according to the parent.
             if (pos/2) {
                 // If the height is not balanced
                 // then we have an invalid value at the
                 // position.
                 if (treeData[pos-1].toInt() == INVALID_DATA) {
                     continue;
                 }

                 QGraphicsLineItem *l = n->plink;
                 QLineF line = l->line();
                 // If the new height of our treeData is N, we have
                 // 2^N leaves. Out of that, we will have 1/2^currHeight
                 // for the subtree rooted at "currHeight". We
                 // want to know that so we can position the nodes
                 // back to where they were before expansion.
                 if ((currHeight != prevHeight) &&
                     (treeData[pos].toInt() != INVALID_DATA) &&
                     (getData(2*(pos-1)) != INVALID_DATA)) {
                     offset = leaves/pow(2,currHeight);
                     prevHeight = currHeight;
                 } else {
                     // Keep the offset the same if the tree is sparse.
                     prevHeight = currHeight;
                     offset = 1;
                 }
                 if (pos%2) {
                     n->pos->setX(parent->pos->x()-(offset*50)); n->pos->setY(n->pos->y()-10);
                     line.setLine(n->pos->x()+25, n->pos->y(), parent->pos->x()+10, parent->pos->y()+20);
                 } else {
                     n->pos->setX(parent->pos->x()+(offset*50)); n->pos->setY(n->pos->y()-10);
                     line.setLine(n->pos->x()+25, n->pos->y(), parent->pos->x()+10, parent->pos->y()+20);
                 }
                 l->setLine(line);
             } else {
                 n->pos->setX(n->pos->x()-newHeight*50);
             }
             // Set the ellipse and text at their right
             // position calculated above
             QGraphicsEllipseItem *e = n->ellipse;
             e->setRect(n->pos->x(), n->pos->y(), 40, 20);
             t->setPos(n->pos->x()+8, n->pos->y());

             //Shrink the scene size to starting size
             qreal new_w = (n->pos->x())*2;
             qreal new_h = ((int)n->pos->y())*2;

             if ((new_w < (int)sceneCoords.width() && new_w > (int)baseCoords.width()) ||
                 (new_h < (int)sceneCoords.height() && new_w > (int)baseCoords.width())) {
                 adjustsceneRect(baseCoords);
             }
         }
         // Set the right value in the text
         t->setPlainText(treeData[pos-1]);
    }
    treeHeight = log2((double)numEntries);
}

void Ui::binaryTree::clearTree()
{
    for (int node=1; node<(numEntries+1); node++) {
        treeData[node-1] = "0";
        cleanupNode(tMap[node]);
    }
    numEntries=0;
}
