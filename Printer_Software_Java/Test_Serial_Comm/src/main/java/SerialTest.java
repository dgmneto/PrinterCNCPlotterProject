import com.fazecast.jSerialComm.*;

import java.io.IOException;
import java.io.InputStream;

public class SerialTest {
    public static void main(String[] args){
        for (SerialPort port: SerialPort.getCommPorts()) {
            System.out.println(port.getSystemPortName());
        }

        SerialPort port = SerialPort.getCommPorts()[0];
        port.setBaudRate(115200);
        port.openPort();
        port.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 100, 0);
        InputStream in = port.getInputStream();
        byte[] arr1 = {100};
        byte[] arr2 = {-100};
        while (true) {
            try {
                Thread.sleep(8000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            port.writeBytes(arr1, 1);
            try {
                System.out.println((int)in.read());
            } catch (IOException e) {
                e.printStackTrace();
            }
            try {
                Thread.sleep(8000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            port.writeBytes(arr2, 1);
            try {
                System.out.println((int)in.read());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
