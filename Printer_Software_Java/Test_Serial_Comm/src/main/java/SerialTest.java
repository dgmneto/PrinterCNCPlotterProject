import com.fazecast.jSerialComm.*;

import java.io.IOException;
import java.io.InputStream;

public class SerialTest {
    public static void main(String[] args){
        SerialCommunicator communicator = new SerialCommunicator();
        communicator.autoconnect(5);

        //Loop for backwards and forward

//        SerialPort port = SerialPort.getCommPorts()[0];
//        port.setBaudRate(115200);
//        port.openPort();
//        port.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 100, 0);
//        InputStream in = port.getInputStream();
//        byte[] arr1 = {100};
//        byte[] arr2 = {-100};
//        try {
//            Thread.sleep(2000);
//        } catch (InterruptedException e) {
//            e.printStackTrace();
//        }
//        port.writeBytes(arr1, 1);
//        boolean spin = false;
//        while (true) {
//            try {
//                byte [] arr = new byte[1];
//                if (in.available() > 0){
//                    in.read(arr);
//                }
//                if (arr[0] == 5){
//                    try {
//                        Thread.sleep(100);
//                    } catch (InterruptedException e) {
//                        e.printStackTrace();
//                    }
//                    if (spin){
//                        port.writeBytes(arr1, 1);
//                    }
//                    else {
//                        port.writeBytes(arr2, 1);
//                    }
//                    spin = !spin;
//                }
//            } catch (IOException e) {
//                e.printStackTrace();
//            }
//        }
    }
}
