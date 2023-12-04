<script lang="ts">
    import { type TableSource, Table } from "@skeletonlabs/skeleton";
    import { tableMapperValues } from "@skeletonlabs/skeleton";
    import type { i2cData } from "./types";

    export let sensorData: i2cData;

    $: tableData = [
        {position: 1, dato: "Temp Ambiente", valor: sensorData?.ambientTemp ?? 'N/A' },
        {position: 1, dato: "Temp Motor", valor: sensorData?.motorTemp ?? 'N/A' },
        {position: 1, dato: "Latitud", valor: sensorData?.latitude ?? 'N/A' },
        {position: 1, dato: "Longitud", valor: sensorData?.longitude ?? 'N/A' },
    ];

    $: tableSimple = {
        head: ['Dato', 'Valor'],
        body: tableMapperValues(tableData, ['dato', 'valor']),
    };
                    
</script>

<div class="m-4 shadow-lg">
    <Table source={tableSimple} />
</div>
