package com.mazzo.andru.testa.gardenapp.controller

import android.annotation.SuppressLint
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothSocket
import android.content.Context
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import android.widget.Toast
import androidx.recyclerview.widget.RecyclerView
import com.mazzo.andru.testa.gardenapp.R
import com.mazzo.andru.testa.gardenapp.Utils
import java.io.IOException

class DeviceAdapter(private var device : MutableList<BluetoothDevice>,
                    private var bluetoothAdapter: BluetoothAdapter,
                    private var context: Context)
    : RecyclerView.Adapter<DeviceAdapter.ViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        return ViewHolder(LayoutInflater.from(parent.context)
                .inflate(R.layout.card_view, parent, false))
    }

    @SuppressLint("MissingPermission")
    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        holder.itemName.text = device[position].name
        holder.itemMac.text = device[position].address

        holder.itemView.setOnClickListener {
            val currentDevice = device[holder.layoutPosition]
            Log.d("connect", "Provo a connettermi")
            ConnectThread(currentDevice, context).run()
        }
    }

    override fun getItemCount(): Int {
        return device.size
    }


    inner class ViewHolder(itemView : View) : RecyclerView.ViewHolder(itemView){
        var itemName : TextView = itemView.findViewById(R.id.name)
        var itemMac : TextView = itemView.findViewById(R.id.mac_address)
    }


    @SuppressLint("MissingPermission")
    private inner class ConnectThread(device: BluetoothDevice, private var context: Context) : Thread() {

        private val mmSocket: BluetoothSocket? by lazy(LazyThreadSafetyMode.NONE) {
            device.createRfcommSocketToServiceRecord(device.uuids[0].uuid)
        }

        override fun run() {
            if(Utils.btSocket == null){
                // Cancel discovery because it otherwise slows down the connection.
                bluetoothAdapter.cancelDiscovery()

                mmSocket?.let { socket ->
                    // Connect to the remote device through the socket. This call blocks
                    // until it succeeds or throws an exception.
                    socket.connect()
                    Log.d("connect", "Connected")

                    Toast.makeText(context, "Dispositivo Connesso", Toast.LENGTH_SHORT).show()
                    // The connection attempt succeeded. Perform work associated with
                    // the connection in a separate thread.
                    Utils.btSocket = socket
                }
            }else{
                Toast.makeText(context, "Il dispositivo risulta connesso", Toast.LENGTH_SHORT).show()
            }
        }

        // Closes the client socket and causes the thread to finish.
        fun cancel() {
            try {
                mmSocket?.close()
            } catch (e: IOException) {
                Log.e("connect", "Could not close the client socket", e)
            }
        }

    }


}