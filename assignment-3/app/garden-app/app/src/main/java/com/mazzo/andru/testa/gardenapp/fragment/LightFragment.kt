package com.mazzo.andru.testa.gardenapp.fragment

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.View
import android.widget.Button
import android.widget.Toast
import com.google.android.material.slider.Slider
import com.mazzo.andru.testa.gardenapp.R
import com.mazzo.andru.testa.gardenapp.model.UIComponents


class LightFragment : Fragment(R.layout.fragment_light), UIComponents {

    private  lateinit var btnLed1 : Button
    private  lateinit var btnLed2 : Button
    private  lateinit var btnLed3 : Button
    private  lateinit var btnLed4 : Button
    private lateinit var slider3 : Slider
    private lateinit var slider4 : Slider

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        if(activity != null){
            this.bindAllComponents()
            this.setAllListeners()
        }
    }

    override fun bindAllComponents() {
        this.btnLed1 = requireActivity().findViewById(R.id.btn_led_1)
        this.btnLed2 = requireActivity().findViewById(R.id.btn_led_2)
        this.btnLed3 = requireActivity().findViewById(R.id.btn_led_3)
        this.btnLed4 = requireActivity().findViewById(R.id.btn_led_4)
        this.slider3 = requireActivity().findViewById(R.id.slider_led_3)
        this.slider4 = requireActivity().findViewById(R.id.slider_led_4)
    }

    override fun setAllListeners() {
        this.btnLed1.setOnClickListener{
            this.switchButton(this.btnLed1)
        }
        this.btnLed2.setOnClickListener{
            this.switchButton(this.btnLed2)
        }
        this.btnLed3.setOnClickListener{
            this.switchButton(this.btnLed3)
            this.switchSlider(this.btnLed3, this.slider3)
        }
        this.btnLed4.setOnClickListener{
            this.switchButton(this.btnLed4)
            this.switchSlider(this.btnLed4, this.slider4)
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
    }

    private fun isButtonInactive(button : Button) : Boolean{
        return button.currentTextColor != requireActivity().getColor(R.color.orange)
    }
}