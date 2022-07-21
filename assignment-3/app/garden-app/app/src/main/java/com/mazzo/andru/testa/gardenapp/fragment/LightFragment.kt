package com.mazzo.andru.testa.gardenapp.fragment

import android.os.Bundle
import android.util.Log
import androidx.fragment.app.Fragment
import android.view.View
import android.widget.Button
import android.widget.Toast
import com.google.android.material.slider.Slider
import com.mazzo.andru.testa.gardenapp.R
import com.mazzo.andru.testa.gardenapp.Utils
import com.mazzo.andru.testa.gardenapp.model.AllarmStatus
import com.mazzo.andru.testa.gardenapp.model.Led
import com.mazzo.andru.testa.gardenapp.model.ManageComponents
import com.mazzo.andru.testa.gardenapp.model.UIComponents
import kotlinx.coroutines.*


class LightFragment : Fragment(R.layout.fragment_light), UIComponents {

    private  lateinit var btnLed1 : Button
    private  lateinit var btnLed2 : Button
    private  lateinit var btnLed3 : Button
    private  lateinit var btnLed4 : Button
    private  lateinit var btnManual : Button
    private lateinit var slider3 : Slider
    private lateinit var slider4 : Slider
    private var allarmStatus = AllarmStatus("192.168.74.207")

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        if(activity != null){
            this.bindAllComponents()
            this.setAllListeners()
            this.refreshView()
            this.allarmStatus.getAllarmStatus {
                if(it == "ALARM"){
                    //Color Bell
                }
            }
            Log.d("connect", Utils.btSocket.toString())
            this.disableAll()
        }
    }

    private fun disableAll() {
        this.btnLed1.isEnabled = false
        this.btnLed2.isEnabled = false
        this.btnLed3.isEnabled = false
        this.btnLed4.isEnabled = false
    }

    private fun enableAll() {
        this.btnLed1.isEnabled = true
        this.btnLed2.isEnabled = true
        this.btnLed3.isEnabled = true
        this.btnLed4.isEnabled = true
    }

    override fun bindAllComponents() {
        this.btnLed1 = requireActivity().findViewById(R.id.btn_led_1)
        this.btnLed2 = requireActivity().findViewById(R.id.btn_led_2)
        this.btnLed3 = requireActivity().findViewById(R.id.btn_led_3)
        this.btnLed4 = requireActivity().findViewById(R.id.btn_led_4)
        this.slider3 = requireActivity().findViewById(R.id.slider_led_3)
        this.slider4 = requireActivity().findViewById(R.id.slider_led_4)
        this.btnManual = requireActivity().findViewById(R.id.btn_manual)
    }

    override fun setAllListeners() {
        this.btnLed1.setOnClickListener{
            this.switchButton(this.btnLed1)
            ManageComponents.switchLedStatus(Led.ONE)
        }
        this.btnLed2.setOnClickListener{
            this.switchButton(this.btnLed2)
            ManageComponents.switchLedStatus(Led.TWO)
        }
        this.btnLed3.setOnClickListener{
            this.switchButton(this.btnLed3)
            this.switchSlider(this.btnLed3, this.slider3)
            ManageComponents.switchLedStatus(Led.THREE)
        }
        this.btnLed4.setOnClickListener{
            this.switchButton(this.btnLed4)
            this.switchSlider(this.btnLed4, this.slider4)
            ManageComponents.switchLedStatus(Led.FOUR)
        }

        this.slider3.addOnChangeListener { _, value, _ ->
            ManageComponents.switchSlider(Led.THREE, value.toInt())
        }

        this.slider4.addOnChangeListener { _, value, _ ->
            ManageComponents.switchSlider(Led.FOUR, value.toInt())
        }

        this.btnManual.setOnClickListener {
            if(Utils.btSocket != null) {
                this.allarmStatus.setManualMode()
                CoroutineScope(Dispatchers.IO).launch {
                    delay(1500)
                    withContext(Dispatchers.Main) {
                        enableAll()
                    }
                }
            }
        }
    }

    private fun changeDrawableActive(button : Button){
        button.setCompoundDrawablesRelativeWithIntrinsicBounds(0, R.drawable.ic_sun_active,0,0)
        button.setTextColor(requireActivity().getColor(R.color.orange))
    }

    private fun changeDrawableInActive(button : Button){
        button.setCompoundDrawablesRelativeWithIntrinsicBounds(0, R.drawable.ic_sun_black,0,0)
        button.setTextColor(requireActivity().getColor(R.color.black))
    }

    private fun switchButton(button: Button){
        if(this.isButtonInactive(button)){
            Toast.makeText(requireContext(), "Start ${button.text}", Toast.LENGTH_SHORT).show()
            this.changeDrawableActive(button)
        }else{
            Toast.makeText(requireContext(), "Stop ${button.text}", Toast.LENGTH_SHORT).show()
            this.changeDrawableInActive(button)
        }
    }

    private fun switchSlider(button: Button, slider: Slider){
        slider.isEnabled = !this.isButtonInactive(button)
        if(!slider.isEnabled){
            slider.value = 1f
        }
    }

    private fun isButtonInactive(button : Button) : Boolean{
        return button.currentTextColor != requireActivity().getColor(R.color.orange)
    }

    private fun refreshView(){
        if(ManageComponents.ledOneStauts != 0) this.switchButton(this.btnLed1)
        if(ManageComponents.ledTwoStauts != 0) this.switchButton(this.btnLed2)
        if(ManageComponents.ledThreeStauts != 0) {
            this.switchButton(this.btnLed3)
            this.switchSlider(this.btnLed3, this.slider3)
        }
        if(ManageComponents.ledFourStauts != 0) {
            this.switchButton(this.btnLed4)
            this.switchSlider(this.btnLed4, this.slider4)
        }
    }
}