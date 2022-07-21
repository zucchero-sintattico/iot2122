package com.mazzo.andru.testa.gardenapp.fragment

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.View
import android.widget.Button
import android.widget.Toast
import com.google.android.material.slider.Slider
import com.mazzo.andru.testa.gardenapp.R
import com.mazzo.andru.testa.gardenapp.Utils
import com.mazzo.andru.testa.gardenapp.model.ManageComponents
import com.mazzo.andru.testa.gardenapp.model.UIComponents

class IrrigationFragment : Fragment(R.layout.fragment_irrigation), UIComponents {

    private lateinit var irrigationButton: Button
    private lateinit var slider: Slider

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        if(activity != null){
            this.bindAllComponents()
            this.setAllListeners()

            if(Utils.btSocket != null){
                ManageComponents.socket = Utils.btSocket
                this.irrigationButton.isEnabled = true
            }else{
                this.irrigationButton.isEnabled = false
            }
        }
    }

    override fun bindAllComponents() {
        this.irrigationButton = requireActivity().findViewById(R.id.btn_irrigation)
        this.slider = requireActivity().findViewById(R.id.slider_irrigation)
    }

    override fun setAllListeners() {
        this.irrigationButton.setOnClickListener {
            this.switchButton(this.irrigationButton)
            ManageComponents.switchIrrigationStatus()
            this.switchSlider(this.irrigationButton, this.slider)
            this.slider.addOnChangeListener { _, value, _ ->
                ManageComponents.changeValueOfIrrigation(value.toInt())
            }
        }
    }

    private fun changeDrawableActive(button : Button){
        button.setCompoundDrawablesRelativeWithIntrinsicBounds(0, R.drawable.ic_rain_active,0,0)
        button.setTextColor(requireActivity().getColor(R.color.orange))
    }

    private fun changeDrawableInActive(button : Button){
        button.setCompoundDrawablesRelativeWithIntrinsicBounds(0, R.drawable.ic_rain_black,0,0)
        button.setTextColor(requireActivity().getColor(R.color.black))
    }

    private fun switchButton(button: Button){
        if(this.isButtonInactive(button)){
            Toast.makeText(requireContext(), "Start Irrigation", Toast.LENGTH_SHORT).show()
            this.changeDrawableActive(button)
        }else{
            Toast.makeText(requireContext(), "Stop Irrigation", Toast.LENGTH_SHORT).show()
            this.changeDrawableInActive(button)
            this.slider.value = 1F
        }
    }

    private fun switchSlider(button: Button, slider: Slider){
        slider.isEnabled = !this.isButtonInactive(button)
    }

    private fun isButtonInactive(button : Button) : Boolean{
        return button.currentTextColor != requireActivity().getColor(R.color.orange)
    }
}