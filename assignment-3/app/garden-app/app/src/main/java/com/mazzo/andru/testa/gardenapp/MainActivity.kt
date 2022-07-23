package com.mazzo.andru.testa.gardenapp

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.mazzo.andru.testa.gardenapp.fragment.ConnectivityFragment
import com.mazzo.andru.testa.gardenapp.fragment.IrrigationFragment
import com.mazzo.andru.testa.gardenapp.fragment.LightFragment
import com.mazzo.andru.testa.gardenapp.model.AllarmStatus
import com.mazzo.andru.testa.gardenapp.model.UIComponents
import nl.joery.animatedbottombar.AnimatedBottomBar

class MainActivity : AppCompatActivity(), UIComponents {

    private val connectivityFragment = ConnectivityFragment()
    private val lightFragment = LightFragment()
    private val irrigationFragment = IrrigationFragment()
    private lateinit var navBar : AnimatedBottomBar

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //Set the first fragment
        Utils.changeCurrentFragment(this@MainActivity, this.connectivityFragment)

        this.bindAllComponents()
        this.setAllListeners()
    }

    override fun bindAllComponents() {
        this.navBar = findViewById(R.id.bottom_bar)
    }

    override fun setAllListeners() {
        this.navBar.onTabSelected = {
            when(it.title){
                "Connection" ->
                    Utils.changeCurrentFragment(this@MainActivity, this.connectivityFragment)

                "Light System" ->
                    Utils.changeCurrentFragment(this@MainActivity, this.lightFragment)

                "Irrigation System" ->
                    Utils.changeCurrentFragment(this@MainActivity, this.irrigationFragment)
            }
        }
    }

    override fun onStop() {
        super.onStop()
        Log.d("TEST_HTTP", "ON DESTROY")
        if (Utils.btSocket != null) {
            Log.d("TEST_HTTP", "MAKING HTTP REQUEST")
            val allarmStatus = AllarmStatus("192.168.74.207")
            allarmStatus.setAutoMode {
            }
        }
    }
}
