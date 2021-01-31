import QtQuick 2.12
import QtQuick.Window 2.12
import QtCharts 2.2
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.2
import QtQml 2.3
import QtQuick.Controls.Styles 1.4
import Connection 1.0
import SensorManager 1.0

/**
 *  @brief  dynamic graph with fetched Data fromDB
 *  Contains propertys to save the user given inputs.
 *  Gridlayout is used for a non static layout at fullscreen.
 *  Every String that gets shown is in qsTr() for an easy language change.
 *  Textfields and Comboboxes are used to fetch the wanted data from DB.
 *  Java functions are for manipulating the graph & comboboxes and convert data to DB readable String
 */


Item {
    id: element

    property string town: ""                    //!<    user given town
    property string sensorLeftAxis: ""          //!<    name of left Y axis from graph
    property string sensorRightAxis: ""         //!<    name of right Y axis from graph
    property string startDate: ""               //!<    user given start date
    property string endDate: ""                 //!<    user given end date
    property string timeValue: ""               //!<    user choice of format for X axis
    property date dateEnd: new Date()           //!<    start date for calc diff to end date
    property date dateStart: new Date()         //!<    end date for calc diff to start date


    GridLayout{
        id: gridLayoutPage

        anchors.fill: parent
        anchors.topMargin: 50                   //value 50 to get more space to back button
        anchors.leftMargin: 15
        anchors.rightMargin: 15
        anchors.bottomMargin: 15

        rows: 9
        columns: 4

        Text{
            id: textAddress

            Layout.row: 0
            Layout.column: 0

            text: qsTr("Stadt")
        }//Text

        TextField{
           id: textFieldAddress

           Layout.row: 0
           Layout.column: 1

           placeholderText: qsTr("Darmstadt")

           background: Rectangle {
                      id: textFieldAddressBorder

                      implicitWidth: 200
                      implicitHeight: 40

                      border.color: "red"
                      border.width: 1
                  }//background rectangle

           onEditingFinished:  {                    //reacts to pressing "Enter" and clicking outside of the Textfield
               print("adress entered and saved: ", textFieldAddress.text)
               town = textFieldAddress.text         //save town
               if(town.length > 0){
                   textFieldAddressBorder.border.color = "green"
               }else{//if town is written
                   textFieldAddressBorder.border.color = "red"
               }//else
               checkInputComplete()                 //check if all needed input for calling DB is entered
           }//onEditingFinished
        }//TextField

        Text{
            id: textTimeData

            Layout.row: 1
            Layout.column: 0

            text: qsTr("Von - Bis")
        }//Text

        TextField{
            id: textFieldStartDate

            Layout.row: 1
            Layout.column: 1

            text: "01.06.2020"                      //first date with data in DB (@date: 08.07.2020)
            inputMask: "99.99.9999"
            inputMethodHints: Qt.ImhDigitsOnly
            validator: RegExpValidator {regExp:  /^(0[1-9]|[12][0-9]|3[01]{1,2}).(0[1-9]|1[0-2]).(19[0-9][0-9]|20[0-9][0-9])/}


            background: Rectangle {
                       id: textFieldStartDateBorder

                       implicitWidth: 200
                       implicitHeight: 40

                       border.color: "red"
                       border.width: 1
                   }//background rectangle

            onEditingFinished:  {                   //reacts to pressing "Enter" and clicking outside of the Textfield
                print("Start Date entered and saved: ", textFieldStartDate.text)
                textFieldStartDateBorder.border.color = "green"
                startDate = textFieldStartDate.text //save start Date
                generateTimeUnits()                 //check for complete date and write time units into Combobox
                checkInputComplete()                //check if all needed input for calling DB is entered
            }//onEditingFinished
        }//TextField

        TextField {
            id: textFieldEndDate

            Layout.row: 1
            Layout.column: 2

            text: "08.06.2020"                      //last date with data in DB (@date: 08.07.2020)
            inputMask: "99.99.9999"
            validator: RegExpValidator {regExp:  /^(0[1-9]|[12][0-9]|3[01]{1,2}).(0[1-9]|1[0-2]).(19[0-9][0-9]|20[0-9][0-9])/}


            background: Rectangle {
                       id: textFieldEndDateBorder

                       implicitWidth: 200
                       implicitHeight: 40

                       border.color: "red"
                       border.width: 1
                   }//background rectangle

            onEditingFinished:  {                   //reacts to pressing "Enter" and clicking outside of the Textfield
                print("End date entered and saved: ", textFieldEndDate.text)
                textFieldEndDateBorder.border.color = "green"
                endDate = textFieldEndDate.text     //save end date
                generateTimeUnits()                 //check for complete date and write time units into Combobox
                checkInputComplete()                //check if all needed input for calling DB is entered
            }//onEditingFinished
        }//TextField


        ComboBox {
             id: comboBoxTimeUnit

             Layout.row: 1
             Layout.column: 3

             background: Rectangle {
                        id: comboBoxTimeUnitBorder

                        implicitWidth: 125
                        implicitHeight: 40

                        color: "light grey"
                        border.color: "red"
                        border.width: 1
                        radius: 10
                    }//background rectangle
             //hoverEnabled: true

             ToolTip.delay: 500
             ToolTip.timeout: 5000
             ToolTip.visible: hovered
             ToolTip.text: qsTr("Zuerst Start und End Datum wählen")

             onActivated:{
                 print("Sensor time unit chosen: " +listModelTimeUnit.get(currentIndex).text)
                 timeValue = listModelTimeUnit.get(currentIndex).text   //save time unit
                 comboBoxTimeUnitBorder.border.color = "green"
                 setDateTimeAxisFormat()            //sets the format for X axis
                 checkInputComplete()               //check if all needed input for calling DB is entered
             }//onActivated

             model: ListModel{                      //gets dynamicly written in java functions
                 id: listModelTimeUnit
             }//ListModel
         }//ComboBox

        Text{
            id: textData

            Layout.row: 2
            Layout.column: 0

            text: qsTr("Daten")
        }//Text

         ComboBox {
             id: comboBoxSensorLeft

             Layout.row: 2
             Layout.column: 1

             displayText: qsTr("Sensor 1")          //just diyplayed if no choice was made


             background: Rectangle {
                        id: comboBoxSensorLeftBorder

                        implicitWidth: 125
                        implicitHeight: 40

                        color: "light grey"
                        border.color: "red"
                        border.width: 1
                        radius: 10
                    }//background rectangle

             onActivated:{
                 print("First sensor chosen: " + listModelSensorLeft.get(currentIndex).text)
                 comboBoxSensorLeftBorder.border.color = "green"
                 sensorLeftAxis = listModelSensorLeft.get(currentIndex).text    //save sensor name for left Y axis
                 displayText = sensorLeftAxis       //change displayed text to chosen sensor
                 checkInputComplete()               //check if all needed input for calling DB is entered
             }//onActivated

             model: ListModel{
                 id: listModelSensorLeft

                 ListElement{
                     text: qsTr("Temperatur")
                 }//ListElement

                 ListElement{
                     text: qsTr("PM 2.5")
                 }//ListElement

                 ListElement{
                     text: qsTr("PM 10")
                 }//ListElement

                 ListElement{
                     text: qsTr("Luftfeuchtigkeit")
                 }//ListElement
             }//ListModel
         }//ComboBox

         ComboBox {
             id: comboBoxSensorRight

             Layout.row: 2
             Layout.column: 2

             displayText: qsTr("Sensor 2")

             background: Rectangle {
                        id: comboBoxSensorRightBorder

                        implicitWidth: 125
                        implicitHeight: 40

                        color: "light grey"
                        //border.color: "red"
                        border.width: 1
                        radius: 10
                    }//background rectangle

             onActivated:{
                 print("Second sensor chosen: " + listModelSensorRight.get(currentIndex).text)
                 sensorRightAxis = listModelSensorRight.get(currentIndex).text      //save sensor name for left Y axis
                 displayText= sensorRightAxis       //change displayed text to chosen sensor
                 checkInputComplete()               //check if all needed input for calling DB is entered
             }//onActivated

             model: ListModel{

                 id: listModelSensorRight

                 ListElement{
                     text: qsTr("Temperatur")
                 }//ListElement

                 ListElement{
                     text: qsTr("PM 2.5")
                 }//ListElement

                 ListElement{
                     text: qsTr("PM 10")
                 }//ListElement

                 ListElement{
                     text: qsTr("Luftfeuchtigkeit")
                 }//ListElement
             }//ListModel
        }//Combobox


        Text{
            id: textMandantoryFields

            Layout.row: 3
            Layout.column: 0


            color: "red"
            text: qsTr("Pflichtfelder")
        }//Text



         ChartView{
             id: graph

             Layout.row: 4
             Layout.rowSpan: 4

             Layout.column: 0
             Layout.columnSpan: 4

             Layout.preferredHeight: parent.height * 0.7
             Layout.preferredWidth: parent.width

             legend.visible: false
             antialiasing: true

             DateTimeAxis {                         //X axis
                 id: axisTime
                 format: ""
                 tickCount: parent.width / 150      //dynamic ticks dependency on width of ChartView
             }//DateTimeAxis

             ValueAxis{
                 id: axisYLeft
                 titleText: sensorLeftAxis
                 min: setMinAxis(sensorLeftAxis)
                 max: setMaxAxis(sensorLeftAxis)
                 labelFormat: setLabelFormat(sensorLeftAxis)
             }//ValueAxis

             ValueAxis{
                 id: axisYRight
                 titleText: sensorRightAxis
                 min: setMinAxis(sensorRightAxis)
                 max: setMaxAxis(sensorRightAxis)
                 labelFormat: setLabelFormat(sensorRightAxis)
             }//ValueAxis

             LineSeries{
                 id: seriesLeft
                 name: sensorLeftAxis
                 axisX: axisTime
                 axisY: axisYLeft
             }//LineSeries

             LineSeries{
                 id: seriesRight
                 name: sensorRightAxis
                 axisX: axisTime
                 axisYRight: axisYRight
             }//LineSeries
         }//ChartView
    }//GridLayout


    /**
     * @brief typechange from Date to milli seconds
     * @param date QDate
     */
    function toMsecsSinceEpoch(date) {
        var msecs = date.getTime();
        return msecs;
    }//function toMsecsSinceEpoch(date)


    /**
     * @brief setter min value for axis
     * @param sensor chosen sensor
     * @return min value of sensor
     */
    function setMinAxis(sensor){
        switch(sensor){
           case qsTr("Temperatur"):
                return -20

           case qsTr("PM 2.5"):
                return 0

           case qsTr("PM 10"):
                return 0

           case qsTr("Luftfeuchtigkeit"):
                return 0

            default:
                return 0
        }//switch(sensor)
    }//function getMinAxis(sensor)


    /**
     * @brief setter max value for axis
     * @param sensor chosen sensor
     * @return max value of sensor
     */
    function setMaxAxis(sensor){
        switch(sensor){
           case qsTr("Temperatur"):
               return 40

           case qsTr("PM 2.5"):
                return 100

           case qsTr("PM 10"):
                return 500

           case qsTr("Luftfeuchtigkeit"):
               return 100

            default:
               return 1
        }//switch(sensor)
    }//function getMaxAxis(sensor)


    /**
     * @brief setter format for DateTimeAxis
     * format is dependent on chosen time unit
     */
    function setDateTimeAxisFormat(){
        switch(timeValue){
            case qsTr("Stunden"):
                axisTime.format= "dd.MM. hh:mm"
                break;
            case qsTr("Tage"):
                axisTime.format= "dd.MM. hh:mm"
                break;
            case qsTr("Wochen"):
                axisTime.format= "dd.MM"
                break;
            default:
                print(qsTr("Irgendwas lief schief"))
                break;
        }//switch(timeValue)
    }//function setDateTimeAxisFormat()


    /**
     * @brief setter labelformat for Y axis
     * @param sensor chosen sensor
     * @return string with labelformat for axis
     */
    function setLabelFormat(sensor){
        switch(sensor){
           case qsTr("Temperatur"):
               return "%d &deg;C"

           case qsTr("PM 2.5"):
               return "%d \xC2\xB5/m^3"

           case qsTr("PM 10"):
               return "%d \xC2\xB5/m^3"

           case qsTr("Luftfeuchtigkeit"):
               return "%d %"

           default:
                return "%d"
        }//switch(sensor)
    }//function getLabelFormat(sensor)


    /**
     * @brief check for generating graph
     * Deletes old points from both LineSeries.
     * if all necessarie inputs are writen (>0), graph gets generated
     */
    function checkInputComplete(){
           eliminateGraphData()
           if(town.length > 0 &&                                                //town entered
                   timeValue.length > 0 &&                                      //time unit chosen (dependence to start and end date)
                   (sensorLeftAxis.length > 0 || sensorRightAxis.length > 0)){  //one/ two sensor/s was/were chosen
               generateGraph()
           }//if needed values for DB call written
    }//function checkInputComplete()


    /**
     * @brief check if start and end date are entered add time unit to ComboBox and set start and end date for X axis
     */
    function generateTimeUnits(){
        if (startDate.length > 0 && endDate.length > 0){
            comboBoxTimeUnit.ToolTip.visible = false
            addTimeValueToCombobox()
            setDateTimeAxisMinMax()
        }//if dates entered
    }//function generateTimeUnits()


    /**
     * @brief setter min and max for DateTimeAxis
     */
    function setDateTimeAxisMinMax(){
        axisTime.min = dateStart
        axisTime.max = dateEnd
    }//function setDateTimeAxisMinMax()


    /**
     * @brief fetches data for left and right Y axis from DB
     */
    function generateGraph(){

        graph.legend.visible = true
        if(sensorLeftAxis.length > 0){
            fetchData(seriesLeft, sensorLeftAxis)

            if(sensorRightAxis.length > 0){
               fetchData(seriesRight, sensorRightAxis)
            }//if right AxisY
        }//if left AxisY
    }//function generateGraph()


    /** @brief fetches the data from DB
     *  @param series container for graph points
     *  @param sensor needed to know which Data (temp, pm2.5, ...) to fetch from DB
     *
     *  needs local date variables because the property ones are non editable via memberfunctions
     *  fetches the data hourly, daily or weekly from DB (user choice)
     *
     *  user chosen sensor vs. DB sensor:
     *  "P1" (pm10) or "P2"(pm2.5) or "temperature" or "humidity"
     *
     *  examples for DB call:
     *  sm.avgCityValue("Dieburg", "P1", "2020-06-02", "2020-06-04")
     *  sm.avgCityValue("Frankfurt", "P2", "2020-06-07T05:00:00Z", "2020-06-07T07:00:00Z")
     *  sm.avgCityValue("Darmstadt", "humidity", "2020-06-01T05:00:00Z", "2020-06-02T05:00:00Z")
     *
     * @TODO checkup for valid entrys -> calls DB for each wanted entry (no entry "code"/ value -9999)
     */
    function fetchData(series, sensor){

        var sensorType = getDbSensor(sensor)
        var periodStart = dateStart
        var periodEnd = dateStart

        switch(timeValue){
            case qsTr("Stunden"):
                periodEnd.setHours(periodEnd.getHours()+1)

                while(periodStart <= dateEnd){
                    series.append(periodStart ,sensorManager.avgCityValue(town, sensorType, convertDateToDbString(periodStart), convertDateToDbString(periodEnd))) //add point with value from DB

                    if(periodEnd.getHours()===23){
                        periodEnd.setDate(periodEnd.getDate()+1)
                        periodEnd.setHours(0)

                    }else{ //if change of Day
                        periodEnd.setHours(periodEnd.getHours() + 1);;
                    }//else

                    if(periodStart.getHours()===23){
                        periodStart.setDate(periodStart.getDate()+1)
                        periodStart.setHours(0)

                    }else{ //if change of Day
                        periodStart.setHours(periodStart.getHours() + 1);;
                    }//else
                }//while data to fetch

                break;
            case qsTr("Tage"):
                periodEnd.setDate(periodEnd.getDate()+1)

                while(periodStart <= dateEnd){
                    series.append(periodStart ,sensorManager.avgCityValue(town, sensorType, convertDateToDbString(periodStart), convertDateToDbString(periodEnd))) //add point with value from DB
                    periodStart.setDate(periodStart.getDate()+1)
                    periodEnd.setDate(periodEnd.getDate()+1)
                }//while data to fetch
                break;

            case qsTr("Wochen"):
                periodEnd.setDate(periodEnd.getDate()+7)

                while(periodStart <= dateEnd){
                    series.append(periodStart ,sensorManager.avgCityValue(town, sensorType, convertDateToDbString(periodStart), convertDateToDbString(periodEnd))) //add point with value from DB
                    periodStart.setDate(periodStart.getDate()+7)
                    periodEnd.setDate(periodEnd.getDate()+7)
                }//while data to fetch
                break;

            default:
                print(qsTr("Irgendwas ist schief gelaufen"))
                break;
        }//switch(timeValue)
    }//function fetchData(series, sensor)


    /** @brief converts a date to string format for DB
     *  @param date Qdate
     *  @return date in string format for DB call
     *
     *  dependency to time unit.
     *
     *  getHours, getDate, getMonth needs a checkup for a leading 0, else there would be problems with the DB.
     *  getMonth counts the months from 0-11.
     */
    function convertDateToDbString(date){
        var dbDateString = ""
        var leadingZeroMonth = ""
        var leadingZeroDay = ""
        var leadingZeroHour = ""

        if(date.getHours() < 10){
            leadingZeroHour = "0"+ date.getHours()
        }else{//if hours
            leadingZeroHour = date.getHours()
        }//else

        if(date.getDate()<10){
            leadingZeroDay = "0"+ date.getDate()
        }else{//if Day
            leadingZeroDay = date.getDate()
        }//else


        if(date.getMonth()<9){ //
            leadingZeroMonth =  "0"+ (date.getMonth()+1)
        }else{//if month
            leadingZeroMonth = (date.getMonth()+1)
        }//else


        if(timeValue === qsTr("Stunden")){
            dbDateString = (date.getFullYear()
                            + "-"
                            + leadingZeroMonth
                            + "-"
                            + leadingZeroDay
                            + "T"
                            + leadingZeroHour
                            + ":00:00Z")
        }else{ //if timeValue hours
            dbDateString = (date.getFullYear()
                            + "-"
                            + leadingZeroMonth
                            + "-"
                            + leadingZeroDay)
        }//else

        return dbDateString
    }//function convertDateToDbString(date)


    /**
     *  @brief converts local sensor to string for DB call
     */
    function getDbSensor(sensor){
        switch (sensor){
            case qsTr("Temperatur"):
                return "temperature"

            case qsTr("PM 2.5"):
                return "P2"

            case qsTr("PM 10"):
                return "P1"

            case qsTr("Luftfeuchtigkeit"):
                return "humidity"
            default:
                return "-1"
        }//switch (sensor)
    }//function getDbSensor(sensor)


    /**
     * @brief removes old points from both series
     */
    function eliminateGraphData(){
        graph.legend.visible = false
        seriesLeft.removePoints(0,seriesLeft.count)
        seriesRight.removePoints(0,seriesRight.count)
    }//function eliminateGraphData()


    /**
     * @brief writes ListElement to Timeunit
     * @param name name of the textfield
     */
    function createTimeValue(name){
        listModelTimeUnit.append({"text": name})
    }//function createTimeValue(name)


    /**
     * @brief eliminates all entry in Timeunit Combobox and clears timeValue
     */
    function destroyTimeValue(){
        comboBoxTimeUnitBorder.border.color = "red"
        //comboBoxTimeUnit.ToolTip.visible = hovered
        listModelTimeUnit.clear()
        timeValue = ""
    }//function destroyTimeValue()


    /**
     * @brief convert string to Qdate and calc the diff in hours
     * @param firstDate first day user want to see on graph
     * @param lastDate last day user want to see on graph
     * @return difference between dates in hours
     */
    function calcHourlyDifference(firstDate, lastDate){

        dateStart = Date.fromLocaleString(Qt.locale(), firstDate, "dd.MM.yyyy")
        dateEnd = Date.fromLocaleString(Qt.locale(), lastDate, "dd.MM.yyyy")

        return (dateEnd - dateStart)/3600000
    }//function  calcHourlyDifference(firstDate, lastDate)


    /**
     * @brief deletes old time units and generates situable new ones
     */
    function addTimeValueToCombobox(){
        var hours = calcHourlyDifference(startDate, endDate)
        destroyTimeValue()
        if(hours >= 24 && hours < 504){ //one Day
            createTimeValue(qsTr("Stunden"))
        }//if one day and less 3 weeks
        if(hours >= 72){            //3days
            createTimeValue(qsTr("Tage"))
        }//if 3 days
        if(hours >= 504){       //3 weeks
            createTimeValue(qsTr("Wochen"))
        }// if 3 weeks
    }//function addTimeValueToCombobox()


    SensorManager{
        id: sensorManager
    }//SensorManager


}//item
