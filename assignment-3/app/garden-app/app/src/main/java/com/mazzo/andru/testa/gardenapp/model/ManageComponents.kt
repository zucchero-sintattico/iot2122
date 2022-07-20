package com.mazzo.andru.testa.gardenapp.model

import android.bluetooth.BluetoothSocket

class ManageComponents() {

    companion object{
        var socket: BluetoothSocket? = null
        private var ledOneStauts = 0
        private var ledTwoStauts = 0
        private var ledThreeStauts = 0
        private var ledFourStauts = 0
        private var irrigatorStatus = 0


        fun switchLedStatus(led : Led){
            when(led){
                Led.ONE -> if(this.ledOneStauts == 0) this.ledOneStauts = 1 else this.ledOneStauts = 0
                Led.TWO -> if(this.ledTwoStauts == 0) this.ledTwoStauts= 1 else this.ledTwoStauts = 0
                Led.THREE -> if(this.ledThreeStauts == 0) this.ledThreeStauts = 1 else this.ledThreeStauts = 0
                Led.FOUR -> if(this.ledFourStauts == 0) this.ledFourStauts = 1 else this.ledFourStauts = 0
            }
            this.sendMessage()
        }

        fun switchSlider(led: Led, value: Int){
            if((led == Led.THREE || led == Led.FOUR) && (value in 0..4)){
                when(led){
                    Led.THREE -> this.ledThreeStauts = value
                    Led.FOUR -> this.ledFourStauts = value
                    else -> {}
                }
            }
            this.sendMessage()
        }


        fun switchIrrigationStatus(){
            if(irrigatorStatus == 0){
                sendOpenIrrigation()
            }else{
                sendCloseIrrigation()
            }
            sendMessage()
        }

        fun changeValueOfIrrigation(value: Int){
            if((value in 1..5)){
                irrigatorStatus = value
            }
            this.sendMessage()
        }

        private fun sendMessage(){
            if(this.socket != null){
                this.socket!!.outputStream.write(("UPDATE:$ledOneStauts," +
                        "$ledTwoStauts," +
                        "$ledThreeStauts," +
                        "$ledFourStauts" +
                        "$irrigatorStatus\n").toByteArray())
            }
        }

        private fun sendOpenIrrigation(){
            if(this.socket != null){
                irrigatorStatus = 1
                this.socket!!.outputStream.write("COMMAND:OPEN_IRRIGATOR".toByteArray())
            }
        }

        private fun sendCloseIrrigation(){
            if(this.socket != null){
                irrigatorStatus = 0
                this.socket!!.outputStream.write("COMMAND:CLOSE_IRRIGATOR".toByteArray())
            }
        }
    }
}