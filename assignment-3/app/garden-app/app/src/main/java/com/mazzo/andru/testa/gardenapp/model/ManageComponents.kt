package com.mazzo.andru.testa.gardenapp.model

import android.bluetooth.BluetoothSocket
import android.util.Log

class ManageComponents{

    companion object{
        var socket: BluetoothSocket? = null
        var ledOneStauts = 0
        var ledTwoStauts = 0
        var ledThreeStauts = 0
        var ledFourStauts = 0
        var irrigatorStatus = 1
        var irrigatorEnabled = false


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
            irrigatorEnabled = if(!irrigatorEnabled){
                sendOpenIrrigation()
                true
            }else{
                sendCloseIrrigation()
                false
            }
        }

        fun changeValueOfIrrigation(value: Int){
            if((value in 1..5)){
                irrigatorStatus = value
            }
            this.sendMessage()
        }

        private fun sendMessage(){
            val message = ("UPDATE:$ledOneStauts," +
                    "$ledTwoStauts," +
                    "$ledThreeStauts," +
                    "$ledFourStauts," +
                    "$irrigatorStatus\n")
            if(this.socket != null){
                this.socket!!.outputStream.write(message.toByteArray())
                Log.d("message", message)
            }
        }

        private fun sendOpenIrrigation(){
            val message = "COMMAND:OPEN_IRRIGATOR\n"
            if(this.socket != null){
                irrigatorStatus = 1
                this.socket!!.outputStream.write(message.toByteArray())
                Log.d("message", message)
            }
        }

        private fun sendCloseIrrigation(){
            val message = "COMMAND:CLOSE_IRRIGATOR\n"
            if(this.socket != null){
                irrigatorStatus = 1
                this.socket!!.outputStream.write(message.toByteArray())
            }
        }
    }
}