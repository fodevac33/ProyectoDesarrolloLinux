<script lang="ts">
  import { onMount, onDestroy } from 'svelte';
  import { browser } from '$app/environment';
  import type { Map, TileLayer, Marker, LatLngExpression } from 'leaflet';
  import type { Data } from '@prisma/client';

  export let sensorData: Data | null;

  let mapElement: HTMLDivElement;
  let map: Map | undefined;

  $: center = [
    sensorData?.latitude,
    sensorData?.longitude
  ] as LatLngExpression

  $: console.log(center);

  onMount(async () => {
    if (browser) {
      const L = await import('leaflet');

      map = L.map(mapElement).setView(center, 16);

      const tileLayer: TileLayer = L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
        attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
      });

      tileLayer.addTo(map);

      const marker: Marker = L.marker(center);
      marker.addTo(map)
        .bindPopup('Mi Moto')
        .openPopup();
    }
  });

  onDestroy(() => {
    map?.remove();
  });
</script>

<div class="m-5 shadow-lg"> 
  <div class="bg-white rounded-lg"> 
    <main>
      <div bind:this={mapElement}></div>
    </main>
  </div>
</div>


<style>
  @import 'leaflet/dist/leaflet.css';
  main div {
      height: 800px;
  }
</style>
