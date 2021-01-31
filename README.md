# Fine Dust Data Visualization

Application to visualize fine dust data on a world map and offer graphs to analyze the data. Group project in the university.
 

# A students guide to QML

Since some of you guys havent developed with Qt and QML we will collect examples and pitfalls of Qt/QML in this Readme. 

> Don't panic!

|  Type   |
|---------|
| Rectangle(https://doc.qt.io/archives/qt-5.10/qml-qtquick-rectangle.html) |
| Text (https://doc.qt.io/archives/qt-5.10/qml-qtquick-text.html)
| Image (https://doc.qt.io/archives/qt-5.10/qml-qtquick-image.html)
| AnimatedSprite](https://doc.qt.io/archives/qt-5.10/qml-qtquick-animatedsprite.html)
| Map (https://doc.qt.io/qt-5/qml-qtlocation-map.html)

A few non-obvious things about QML:

- The Z-Index (i.e. how visible objects are stacked and how they cover each other)
is determined by the order of the elements in the QML file. (Top in the file
is furthest away / at the bottom of the stack.) \
Update: I just found out that
the [z property](https://doc.qt.io/qt-5/qml-qtquick-item.html#z-prop) also exists.
- [Anchors](https://doc.qt.io/qt-5/qtquick-positioning-anchors.html) can be 
your friend when positioning elements relative to each other. `anchors.centerIn`
and `anchors.fill` are nice shortcuts.
- QML does not have variables but properties. It is very easy and common to
create bound properties, e.g. `width: Math.max(somerec.width, otherrec.width)`
This means that changes are 
automatically propagated to all dependent properties. This is very convenient
most of the times but can cause headaches in some cases.
- Child elements coordinate system has its origin at the top left corner of
the parent.
- You might stumble upon `childrenRect` but I would not recommend using it, 
since it does not shrink in size, e.g. when the aspect ratio or user editable
text changes.