var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
//сервіси які будуть доступні в усій програмі
builder.Services.AddControllersWithViews();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
    app.UseHsts();
}

app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();

app.UseAuthorization();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");

// here is main function where instead of executing my code,
// framework takes initiative and grabs the control flow to the end
// of an execution session of the application (Inversion of controller)
await app.RunAsync();