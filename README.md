# LEDToggle demo
This is a simple demo that allows one to toggle a led with a simple qt application. The demo is split in a backend and into a frontend. The frontend can also run with webassembly so that the same UI can be used twice. It uses websockets to communicate between frontend and backend. The demo should run on all qt based BSPs.  
The backend searches for a gpio with the name "led". For this it uses the dev gpio character device inteface of Linux. The names can be set in a devicetree as follows (example devictree overlay for iMX6):  
```
/dts-v1/;
/plugin/;
/ {
	compatible = "toradex,colibri-imx6dl";
	fragment@0 {
		target-path = "/soc/aips-bus@2000000/gpio@20a0000";
		__overlay__{
			gpio-line-names = "gpio2_0", "gpio2_1", "gpio2_2","gpio2_3","gpio2_4","gpio2_5","gpio2_6","gpio2_7","led","gpio2_9","gpio2_10","gpio2_11","gpio2_12","gpio2_13","gpio2_14","gpio2_15","gpio2_16","gpio2_17","gpio2_18","gpio2_19","gpio2_20","gpio2_21","gpio2_22","gpio2_23","gpio2_24","gpio2_25","gpio2_26","gpio2_27","gpio2_28","gpio2_29","gpio2_30","gpio2_31";
		};
	};
};
```

If using webassembly to allow the frontend to automatically connect to the backend from any host the LEDToggleFrontend.html needs to be adjusted as follows:
```
--- LEDToggleFrontend.html.orig 2019-11-02 20:02:56.531653741 +0100
+++ LEDToggleFrontend.html 2019-11-02 19:07:29.530684102 +0100
@@ -56,6 +56,7 @@
                   spinner.style.display = 'none';
                   canvas.style.display = 'block';
               },
+              environment:{"hostname": window.location.hostname}
           });
           qtLoader.loadEmscriptenModule("LEDToggleFrontend");
       }
```

