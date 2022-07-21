package com.mazzo.andru.testa.gardenapp

import android.bluetooth.BluetoothSocket
import androidx.appcompat.app.AppCompatActivity
import androidx.fragment.app.Fragment

class Utils {

    companion object{

        var btSocket : BluetoothSocket? = null

        fun changeCurrentFragment(activity: AppCompatActivity, fragment: Fragment){
            val transaction = activity.supportFragmentManager.beginTransaction()
            transaction.replace(R.id.fragment_container, fragment, fragment.tag)
            transaction.addToBackStack(fragment.tag)
            transaction.commit()
        }


    }
}