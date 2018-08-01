#!/usr/bin/python2
import _VehicleAnalyze as va


class IVehicleAnalyze:
    def __init__(self,model_dir,gpu_id,frameskip,numnull):
        self.__analyzer = va.VehicleAnalyze(model_dir,gpu_id,frameskip,numnull)

    def input(self,filepath):
        self.__analyzer.input(filepath)

    def get_trackers(self):
        return self.__analyzer.get_trackers()


if __name__=="__main__":
    model_dir = "/home/zqp/install_lib/models"
    vehicleAnalyzer = IVehicleAnalyze(model_dir,0,10,1)
