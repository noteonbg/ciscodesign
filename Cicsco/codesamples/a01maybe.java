public class NetworkConnectionPool {
    private static NetworkConnectionPool instance;
    private List<Connection> connections;

    private NetworkConnectionPool() {
        // Initialize connection pool
        connections = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            connections.add(new Connection());
        }
    }

    public static synchronized NetworkConnectionPool getInstance() {
        if (instance == null) {
            instance = new NetworkConnectionPool();
        }
        return instance;
    }

    public Connection getConnection() {
        if (connections.isEmpty()) {
            throw new IllegalStateException("No connections available in the pool");
        }
        return connections.remove(0);
    }

    public void releaseConnection(Connection connection) {
        connections.add(connection);
    }
}

public class Connection {
    // Implement connection details
}



public interface Protocol {
    void sendData(byte[] data);
    void receiveData();
}

public class TCPProtocol implements Protocol {
    @Override
    public void sendData(byte[] data) {
        // Implement TCP sending logic
        System.out.println("Sending data via TCP");
    }

    @Override
    public void receiveData() {
        // Implement TCP receiving logic
        System.out.println("Receiving data via TCP");
    }
}

public class UDPProtocol implements Protocol {
    @Override
    public void sendData(byte[] data) {
        // Implement UDP sending logic
        System.out.println("Sending data via UDP");
    }

    @Override
    public void receiveData() {
        // Implement UDP receiving logic
        System.out.println("Receiving data via UDP");
    }
}

public class ProtocolFactory {
    public Protocol createProtocol(String type) {
        if (type.equalsIgnoreCase("TCP")) {
            return new TCPProtocol();
        } else if (type.equalsIgnoreCase("UDP")) {
            return new UDPProtocol();
        } else {
            throw new IllegalArgumentException("Unknown protocol type");
        }
    }
}

import java.util.ArrayList;
import java.util.List;

public interface NetworkObserver {
    void update(String event);
}

public class NetworkObservable {
    private List<NetworkObserver> observers = new ArrayList<>();

    public void addObserver(NetworkObserver observer) {
        observers.add(observer);
    }

    public void removeObserver(NetworkObserver observer) {
        observers.remove(observer);
    }

    public void notifyObservers(String event) {
        for (NetworkObserver observer : observers) {
            observer.update(event);
        }
    }

    // Example method to trigger network events
    public void networkEventOccurred(String event) {
        notifyObservers(event);
    }
}

public class NetworkLogger implements NetworkObserver {
    @Override
    public void update(String event) {
        System.out.println("Logging network event: " + event);
    }
}

public class NetworkUIUpdater implements NetworkObserver {
    @Override
    public void update(String event) {
        System.out.println("Updating UI with network event: " + event);
    }
}

public interface DataStrategy {
    void apply(byte[] data);
}

public class EncryptionStrategy implements DataStrategy {
    @Override
    public void apply(byte[] data) {
        // Implement encryption logic
        System.out.println("Encrypting data...");
    }
}

public class CompressionStrategy implements DataStrategy {
    @Override
    public void apply(byte[] data) {
        // Implement compression logic
        System.out.println("Compressing data...");
    }
}

public class DataProcessor {
    private DataStrategy strategy;

    public void setStrategy(DataStrategy strategy) {
        this.strategy = strategy;
    }

    public void processData(byte[] data) {
        strategy.apply(data);
    }
}

public interface Network {
    void sendData(byte[] data);
    void receiveData();
}

public class RealNetwork implements Network {
    @Override
    public void sendData(byte[] data) {
        // Implement sending data over the network
        System.out.println("Sending data over the network");
    }

    @Override
    public void receiveData() {
        // Implement receiving data over the network
        System.out.println("Receiving data over the network");
    }
}

public class NetworkProxy implements Network {
    private RealNetwork realNetwork;

    public NetworkProxy() {
        // Optionally initialize realNetwork
        realNetwork = new RealNetwork();
    }

    @Override
    public void sendData(byte[] data) {
        // Perform additional logging or security checks
        System.out.println("Proxy: Logging data transmission");
        realNetwork.sendData(data);
    }

    @Override
    public void receiveData() {
        // Perform additional logging or security checks
        System.out.println("Proxy: Logging data reception");
        realNetwork.receiveData();
    }
}

public class Main {
    public static void main(String[] args) {
        // Singleton Example
        NetworkConnectionPool connectionPool = NetworkConnectionPool.getInstance();
        Connection conn1 = connectionPool.getConnection();
        Connection conn2 = connectionPool.getConnection();
        connectionPool.releaseConnection(conn1);
        connectionPool.releaseConnection(conn2);

        // Factory Example
        ProtocolFactory protocolFactory = new ProtocolFactory();
        Protocol tcpProtocol = protocolFactory.createProtocol("TCP");
        tcpProtocol.sendData(new byte[]{1, 2, 3});
        Protocol udpProtocol = protocolFactory.createProtocol("UDP");
        udpProtocol.sendData(new byte[]{4, 5, 6});

        // Observer Example
        NetworkObservable observable = new NetworkObservable();
        NetworkObserver logger = new NetworkLogger();
        NetworkObserver uiUpdater = new NetworkUIUpdater();
        observable.addObserver(logger);
        observable.addObserver(uiUpdater);
        observable.networkEventOccurred("Connection established");

        // Strategy Example
        DataProcessor processor = new DataProcessor();
        processor.setStrategy(new EncryptionStrategy());
        processor.processData(new byte[]{7, 8, 9});
        processor.setStrategy(new CompressionStrategy());
        processor.processData(new byte[]{10, 11, 12});

        // Proxy Example
        Network network = new NetworkProxy();
        network.sendData(new byte[]{13, 14, 15});
        network.receiveData();
    }
}
