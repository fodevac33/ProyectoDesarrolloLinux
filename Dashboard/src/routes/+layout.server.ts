import type { LayoutServerLoad } from './$types';
import { fetchLatestReading } from '$lib/primsa';

export const load = (async () => {
    const data = await fetchLatestReading();

    return { sensorData: data };
}) satisfies LayoutServerLoad;