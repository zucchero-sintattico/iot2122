package com.mazzo.andru.testa.gardenapp.controller

import android.annotation.SuppressLint
import android.bluetooth.BluetoothDevice
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.mazzo.andru.testa.gardenapp.R

class DeviceAdapter(private var device : MutableList<BluetoothDevice>)
    : RecyclerView.Adapter<DeviceAdapter.ViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        return ViewHolder(LayoutInflater.from(parent.context)
                .inflate(R.layout.card_view, parent, false))
    }

    @SuppressLint("MissingPermission")
    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        holder.itemName.text = device[position].name
        holder.itemMac.text = device[position].address
    }

    override fun getItemCount(): Int {
        return device.size
    }


    inner class ViewHolder(itemView : View) : RecyclerView.ViewHolder(itemView){
        var itemName : TextView = itemView.findViewById(R.id.name)
        var itemMac : TextView = itemView.findViewById(R.id.mac_address)
    }
}