package com.mazzo.andru.testa.gardenapp.fragment

import android.Manifest
import android.app.Activity
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothManager
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.IntentFilter
import android.content.pm.PackageManager
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.View
import android.widget.Button
import android.widget.Toast
import androidx.activity.result.contract.ActivityResultContracts
import androidx.core.app.ActivityCompat
import androidx.recyclerview.widget.RecyclerView
import com.mazzo.andru.testa.gardenapp.R
import com.mazzo.andru.testa.gardenapp.controller.DeviceAdapter
import com.mazzo.andru.testa.gardenapp.model.UIComponents

class ConnectivityFragment : Fragment(R.layout.fragment_connectivity), UIComponents{

    private lateinit var buttonScan : Button
    private lateinit var bluetoothManager : BluetoothManager
    private lateinit var bluetoothAdapter : BluetoothAdapter
    private lateinit var recyclerView : RecyclerView
    private lateinit var recyclerAdapter : DeviceAdapter
    private var devices : MutableList<BluetoothDevice> = mutableListOf()

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        if(activity != null){
            this.bindAllComponents()
            this.setAllListeners()
        }

    }

    override fun onResume() {
        super.onResume()

        if(activity != null){
            this.bluetoothManager = requireActivity().getSystemService(BluetoothManager::class.java)
            this.bluetoothAdapter = this.bluetoothManager.adapter
        }
    }

    override fun bindAllComponents() {
        this.buttonScan = requireActivity().findViewById(R.id.btn_scan)
        this.recyclerView = requireActivity().findViewById(R.id.recycler_device)
    }

    override fun setAllListeners() {
        this.buttonScan.setOnClickListener {
            if(bluetoothAdapter != null){
                if(bluetoothAdapter.isEnabled){
                    this.getBondedDevices()
                    this.updateUI()
                    val filter = IntentFilter(BluetoothDevice.ACTION_FOUND)
                    requireActivity().registerReceiver(receiver, filter)
                    Toast.makeText(requireContext(), "Scan Devices", Toast.LENGTH_SHORT).show()
                }else{
                    val enableBluetoothIntent = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
                    resultLauncher.launch(enableBluetoothIntent)
                }
            }else{
                Toast.makeText(requireContext(),
                    "Bluetooth is not supported :(", Toast.LENGTH_SHORT).show()
            }
        }
    }

    private var resultLauncher = registerForActivityResult(ActivityResultContracts.StartActivityForResult()){ result ->
        if(result.resultCode == Activity.RESULT_OK){
            //Scan Bluetooth device
            this.updateUI()
        }else{
            Toast.makeText(requireContext(),
                "Bluetooth is not enabled, please enable it :<", Toast.LENGTH_SHORT).show()
        }
    }

    //Implement Request Permission
    private fun checkBluetoothPermission(){

    }

    private fun getBondedDevices() {
        if (ActivityCompat.checkSelfPermission(
                requireContext(),
                Manifest.permission.BLUETOOTH_CONNECT
            ) != PackageManager.PERMISSION_GRANTED
        ) {
            // TODO: Consider calling
            //    ActivityCompat#requestPermissions
            // here to request the missing permissions, and then overriding
            //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
            //                                          int[] grantResults)
            // to handle the case where the user grants the permission. See the documentation
            // for ActivityCompat#requestPermissions for more details.
            return
        }
        this.devices.addAll(this.bluetoothAdapter.bondedDevices)
    }

    private fun updateUI(){
        this.recyclerView.adapter = DeviceAdapter(this.devices)
    }

    private val receiver = object : BroadcastReceiver() {
        override fun onReceive(context: Context, intent: Intent) {
            when (intent.action) {
                BluetoothDevice.ACTION_FOUND -> {
                    // Discovery has found a device. Get the BluetoothDevice
                    // object and its info from the Intent.
                    val device: BluetoothDevice? =
                        intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE)
                    if (device != null) {
                        devices.add(device)
                        updateUI()
                    }
                }

            }

        }
    }


    override fun onDestroy() {
        super.onDestroy()
        if(activity != null){
            requireActivity().unregisterReceiver(receiver)
        }
    }
}