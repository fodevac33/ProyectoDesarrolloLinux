import type { Data } from "@prisma/client";

export const updateSensorData = async (): Promise<Data | null> => {
    try {
        const response = await fetch('/api/latest'); // replace with your actual API endpoint
        if (response.ok) {
            const newData = await response.json() as Data;
            return newData;
        } else {
            throw new Error('Failed to fetch sensor data');
        }
    } catch (error) {
        console.error('Error fetching sensor data:', error);
        return null
    }
}