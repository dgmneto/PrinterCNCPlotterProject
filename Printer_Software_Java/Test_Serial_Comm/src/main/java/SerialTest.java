import com.fazecast.jSerialComm.*;

import java.io.IOException;
import java.io.InputStream;

public class SerialTest {
    public static void main(String[] args) {
        SerialCommunicator communicator = new SerialCommunicator();
        communicator.autoconnect(20);

        //Loop for backwards and forward in the X axis
//        byte[] forward = {(byte) 255, (byte) 0b00000000, 0, 0, 0, 0, 0, 0, 0};
//        byte[] backward = {(byte) 255, (byte) 0b00000010, 0, 0, 0, 0, 0, 0, 0};
        byte[] forward = {0, 0, (byte) 255, (byte) 0b00000000, 0, 0, 0, 0, 0};
        byte[] backward = {0, 0, (byte) 255, (byte) 0b00000010, 0, 0, 0, 0, 0};

        System.out.println("Writting data");

        communicator.writeData(forward);

        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        boolean spin = false;

        while (true) {
            byte[] arr = new byte[1];
            if (communicator.available() > 0) {
                communicator.read(arr);
            }
            if (arr[0] == 5) {
                if (spin) {
                    communicator.writeData(forward);
                } else {
                    communicator.writeData(backward);
                }
                spin = !spin;
            }
        }
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
    }
}
